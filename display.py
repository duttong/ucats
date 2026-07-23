#! /usr/bin/env python
""" Chromatogram plotting and main display window for UCATS.

    ChromDisplay is ported from FE3_acquisition/display.py's ChromDisplay,
    adapted for UCATS's 3 named GC channels (ch1/ch2/ch3) and smart.py's
    GCChannels buffers instead of FE3's gc7890.py detector-data dict.

    UCATSDisplay combines it with display_panel.DisplayPanel into the
    operator window, following FE3's fe3display layout: matplotlib's
    Qt5Agg backend manages the chromatogram as its own top-level window
    (sharing the Qt event loop) rather than being embedded in the panel.
"""

import sys
from time import time

import matplotlib
matplotlib.use('Qt5Agg')    # noqa
import matplotlib.pyplot as plt
import numpy as np

from PyQt5 import QtWidgets, QtCore

from display_panel import DisplayPanel, CHANNEL_MOLECULES


class ChromDisplay:
    """ matplotlib chromatogram display for the UCATS 3-channel GC. """

    def __init__(self, instrument):
        self.instrument = instrument
        self.channel_names = list(instrument.gc_channels.channels.keys())
        self.color = {'ch1': 'darkred', 'ch2': 'darkgreen', 'ch3': 'darkblue'}
        self.plotted = []
        self.fig = None
        self.texttop = 0.965

    def canvas(self, xsize=8, ysize=6):
        plt.rcParams['figure.figsize'] = [xsize, ysize]
        self.fig, self.axs = plt.subplots(len(self.channel_names), 1)
        self.fig.subplots_adjust(top=0.900, bottom=0.080, left=0.110, right=0.950, hspace=0.300)
        self.default_settings()
        return self.fig

    def default_settings(self):
        self.fig.text(0.4, self.texttop, 'UCATS GC', fontsize=14)
        for ax, name in zip(self.fig.axes, self.channel_names):
            ax.autoscale(enable=True, axis='x', tight=False)
            ax.autoscale(enable=True, axis='y', tight=False)
            ax.set_ylabel('Response (Hz)')
            if name == self.channel_names[-1]:
                ax.set_xlabel('Time (s)')

    def update(self):
        """ Redraw the current injection's chromatogram traces. """
        for p in self.plotted:
            p.remove()
        self.plotted = []

        inst = self.instrument
        chromduration = inst.setup['chromduration']
        backflush_times = inst.setup.get('backflush_times', {})

        chrom_time = (time() - inst.injection_t0) if inst.injection_t0 else 0
        p = self.fig.text(0.02, self.texttop, f'{inst.gc_state} injection, t={chrom_time:.0f}s', fontsize=12)
        self.plotted.append(p)

        for ax, name in zip(self.fig.axes, self.channel_names):
            mol = CHANNEL_MOLECULES.get(name)
            ax.set_title(f'Channel {name} ({mol})' if mol else f'Channel {name}')

            if name in backflush_times:
                p = ax.axvline(x=backflush_times[name], color='gainsboro')
                self.plotted.append(p)

            y = inst.gc_channels.channels[name].snapshot()
            if y:
                x = np.linspace(0, chromduration, len(y))
                p, = ax.plot(x, y, '-', color=self.color.get(name, 'steelblue'))
                self.plotted.append(p)
                p, = ax.plot(x[-1], y[-1], 'o', color=self.color.get(name, 'steelblue'))
                self.plotted.append(p)

        plt.draw()


class UCATSDisplay(QtWidgets.QMainWindow):
    """ Main operator window: DisplayPanel readouts/controls as the central
        widget, plus a separate matplotlib Qt5Agg chromatogram window, both
        refreshed on a 1 s QTimer. """

    def __init__(self, instrument):
        super().__init__()
        self.instrument = instrument
        self.setWindowTitle('UCATS')

        self.panel = DisplayPanel(instrument)
        self.setCentralWidget(self.panel)

        self.chrom = ChromDisplay(instrument)
        self.fig = self.chrom.canvas()
        plt.draw()
        plt.pause(0.001)

        self.timer_chrom = QtCore.QTimer()
        self.timer_chrom.timeout.connect(self.chrom.update)
        self.timer_chrom.start(1000)

        self.timer_panel = QtCore.QTimer()
        self.timer_panel.timeout.connect(self.refresh_panel)
        self.timer_panel.start(1000)

    def refresh_panel(self):
        self.panel.update_time()
        if not self.instrument.eng_df.empty:
            row = self.instrument.eng_df.iloc[-1].to_dict()
            self.panel.update_display_data(row)

    def closeEvent(self, event):
        self.instrument.shutdown()
        event.accept()


if __name__ == '__main__':
    """ UI-only preview, no hardware: python display.py """
    import ucats

    app = QtWidgets.QApplication(sys.argv)

    instrument = ucats.Instrument_UCATS.__new__(ucats.Instrument_UCATS)
    instrument.setup = {'chromduration': 75, 'backflush_times': {'ch2': 40, 'ch3': 20}}
    instrument.mode = 'flight'
    instrument.gc_state = 'idle'
    instrument.injection_t0 = None
    import pandas as pd
    instrument.eng_df = pd.DataFrame()

    from smart import GCChannels, GCChannel
    instrument.gc_channels = GCChannels.__new__(GCChannels)
    instrument.gc_channels.channels = {
        'ch1': GCChannel('ch1', 0), 'ch2': GCChannel('ch2', 1), 'ch3': GCChannel('ch3', 2)}

    instrument.start = lambda: None
    instrument.shutdown = lambda: None
    instrument.set_mode = lambda mode: setattr(instrument, 'mode', mode)

    window = UCATSDisplay(instrument)
    window.show()
    sys.exit(app.exec_())
