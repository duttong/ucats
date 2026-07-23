#! /usr/bin/env python
""" Operator panel for the UCATS GC.

    Modeled on ucats-b/display_panel.py: a plain QWidget with a live-value
    grid, toggle buttons, and simple state -- not FE3's flask-sampler UI
    (barcode scanner, cal tank tables, manifold pump-down), none of which
    applies to UCATS.
"""

import sys
import datetime
import logging
from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QGridLayout, QLabel, QPushButton,
    QApplication, QMessageBox, QFrame,
)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt

logger = logging.getLogger(__name__)


class HeartbeatIndicator(QLabel):
    """ Small circular watchdog light, styled after ucats-b/display_panel.py's
        PilotIndicator. Toggles color between ticks of ucats.py's
        _heartbeat_pulse() (the ER-2 aircraft-interface watchdog line --
        see config.yaml's devices.adr2000.dig.heartbeat), so a color that's
        stuck (not alternating) on the running instrument means that 1 Hz
        task has stalled or acquisition isn't running. """

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setFixedSize(20, 20)
        self.setAutoFillBackground(True)
        self.update_indicator(False)

    def update_indicator(self, value):
        color = 'LightSkyBlue' if value else 'yellow'
        self.setStyleSheet(f'background-color: {color}; border: 1px solid black; border-radius: 10px;')


# Instrument-wide readouts, not tied to one GC channel -- shown above the
# per-channel block below. (eng_row() key, display label) -- see ucats.py's
# Instrument_UCATS.eng_row()
GENERAL_READOUTS = [
    ('gc_state', 'GC state'),
    ('air_cal_mode', 'Mode'),
    ('ssv_cal_pos', 'Cal SSV pos'),
    ('sampIN', 'Sample loop IN'),
    ('sampOUT', 'Sample loop OUT'),
    ('ssv', 'Air/Cal solenoid'),
]

CHANNELS = ['ch1', 'ch2', 'ch3']

# Target compound(s) per channel, for the column header only -- keep in
# sync with config.yaml's gc_channels[].molecules (confirmed there against
# flight/src/int.tmc/intdsp.tmc/intres.tmc).
CHANNEL_MOLECULES = {
    'ch1': 'CH4',
    'ch2': 'CFC12/CFC11',
    'ch3': 'N2O/SF6',
}

# Per-channel readouts, one column per channel in CHANNELS -- (display
# label, eng_row() key template, channels the row applies to or None for
# all). ch1/ch2 have no post-column Omega zone (see config.yaml), so
# 'Post (C)' is only drawn for ch3 -- the other two columns just leave that
# grid cell blank rather than showing a permanent N/A.
CHANNEL_ROWS = [
    ('ECD (Hz)', 'ecdA_{ch}', None),
    ('ECD (C)', 'omega_{ch}_ecd', None),
    ('Col (C)', 'omega_{ch}_col', None),
    ('Post (C)', 'omega_{ch}_post', {'ch3'}),
    ('GSV', 'gsv_{ch}', None),
]


class DisplayPanel(QWidget):
    """ Live readouts + calibration-mode toggle + start/stop for Instrument_UCATS.

        instrument, if given, is the Instrument_UCATS this panel controls --
        pass None for a UI-only preview (`python display_panel.py`).
    """

    def __init__(self, instrument=None):
        super().__init__()
        self.instrument = instrument
        self.button_font = 'font-size: 16px;'
        self.start_time = datetime.datetime.now()
        self.data_labels = {}
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()
        layout.setContentsMargins(10, 10, 10, 10)
        layout.setSpacing(12)

        top_layout = QHBoxLayout()
        self.time_label = QLabel()
        self.update_time()
        top_layout.addWidget(self.time_label, alignment=Qt.AlignLeft)
        self.heartbeat_indicator = HeartbeatIndicator(self)
        top_layout.addWidget(self.heartbeat_indicator, alignment=Qt.AlignRight)
        layout.addLayout(top_layout)

        general_grid = QGridLayout()
        general_grid.setSpacing(8)
        for row, (key, label_text) in enumerate(GENERAL_READOUTS):
            label = QLabel(f'{label_text}: ')
            label.setFont(QFont('Arial', 13))
            general_grid.addWidget(label, row, 0, alignment=Qt.AlignLeft)

            value = QLabel('N/A')
            value.setFont(QFont('Arial', 13))
            value.setStyleSheet('color: #11e;')
            general_grid.addWidget(value, row, 1, alignment=Qt.AlignRight)
            self.data_labels[key] = value
        layout.addLayout(general_grid)

        divider = QFrame()
        divider.setFrameShape(QFrame.HLine)
        divider.setFrameShadow(QFrame.Sunken)
        layout.addWidget(divider)

        # === Per-channel block: ch1/ch2/ch3 side by side, one column each ===
        channel_grid = QGridLayout()
        channel_grid.setHorizontalSpacing(24)
        channel_grid.setVerticalSpacing(6)
        for col, ch in enumerate(CHANNELS):
            header = QVBoxLayout()
            header.setSpacing(0)
            name_label = QLabel(ch.upper())
            name_label.setFont(QFont('Arial', 14, QFont.Bold))
            name_label.setAlignment(Qt.AlignCenter)
            header.addWidget(name_label)

            mol_label = QLabel(f'({CHANNEL_MOLECULES.get(ch, "")})')
            mol_label.setFont(QFont('Arial', 10))
            mol_label.setAlignment(Qt.AlignCenter)
            header.addWidget(mol_label)

            channel_grid.addLayout(header, 0, col)

            for row, (label_text, key_template, applies_to) in enumerate(CHANNEL_ROWS, start=1):
                if applies_to is not None and ch not in applies_to:
                    continue    # e.g. ch1/ch2 have no Post zone -- leave the cell blank
                key = key_template.format(ch=ch)

                cell = QVBoxLayout()
                cell.setSpacing(0)
                label = QLabel(label_text)
                label.setFont(QFont('Arial', 11))
                label.setAlignment(Qt.AlignCenter)
                cell.addWidget(label)

                value = QLabel('N/A')
                value.setFont(QFont('Arial', 13))
                value.setStyleSheet('color: #11e;')
                value.setAlignment(Qt.AlignCenter)
                cell.addWidget(value)

                channel_grid.addLayout(cell, row, col)
                self.data_labels[key] = value
        layout.addLayout(channel_grid)

        # === Calibration mode toggle: flight uses the ADR2000 digital ssv
        # solenoid, calibration uses an external Valco SSV (see config.yaml's
        # 'mode' and ucats.py's Instrument_UCATS.set_mode()). ===
        self.cal_mode_button = QPushButton('Flight Mode')
        self.cal_mode_button.setCheckable(True)
        self.cal_mode_button.setChecked(
            bool(self.instrument is not None and getattr(self.instrument, 'mode', 'flight') == 'calibration'))
        self._style_mode_button()
        self.cal_mode_button.clicked.connect(self.toggle_mode)
        layout.addWidget(self.cal_mode_button)

        # === Start/Stop acquisition ===
        self.run_button = QPushButton('Start Acquisition')
        self.run_button.setCheckable(True)
        self.run_button.setStyleSheet(
            f'background-color: DarkSeaGreen; color: black; border: 1px solid #CC9999; {self.button_font}')
        self.run_button.clicked.connect(self.toggle_run)
        layout.addWidget(self.run_button)

        shutdown_button = QPushButton('SHUTDOWN')
        shutdown_button.clicked.connect(self.shutdown_menu)
        shutdown_button.setStyleSheet(
            f'background-color: DarkRed; color: white; border: 1px solid #CC9999; {self.button_font}')
        layout.addWidget(shutdown_button)

        self.setLayout(layout)

    def update_time(self):
        now = datetime.datetime.now()
        elapsed = str(now - self.start_time).split('.')[0]
        self.time_label.setText(
            f"<span style='font-size:18px; font-weight:bold;'>{now:%Y-%m-%d %H:%M:%S}</span><br>"
            f"<span style='font-size:14px;'>Elapsed: {elapsed}</span>"
        )

    def update_display_data(self, row):
        """ row is a dict shaped like Instrument_UCATS.eng_row()'s output. """
        for key, label in self.data_labels.items():
            if key not in row:
                continue
            value = row[key]
            text = f'{value:.2f}' if isinstance(value, float) else str(value)
            label.setText(text)

        if 'heartbeat' in row:
            self.heartbeat_indicator.update_indicator(row['heartbeat'])

    def _style_mode_button(self):
        cal = self.cal_mode_button.isChecked()
        self.cal_mode_button.setText('Calibration Mode' if cal else 'Flight Mode')
        self.cal_mode_button.setStyleSheet(
            f"background-color: {'DodgerBlue' if cal else 'DarkSeaGreen'}; "
            f"color: {'white' if cal else 'black'}; "
            f"border: 1px solid #CC9999; {self.button_font}")

    def toggle_mode(self):
        mode = 'calibration' if self.cal_mode_button.isChecked() else 'flight'
        if self.instrument is not None:
            self.instrument.set_mode(mode)
        self._style_mode_button()

    def toggle_run(self):
        if self.run_button.isChecked():
            if self.instrument is not None:
                self.instrument.start()
            self.run_button.setText('Stop Acquisition')
            self.run_button.setStyleSheet(
                f'background-color: DodgerBlue; color: white; border: 1px solid #CC9999; {self.button_font}')
        else:
            if self.instrument is not None:
                self.instrument.shutdown()
            self.run_button.setText('Start Acquisition')
            self.run_button.setStyleSheet(
                f'background-color: DarkSeaGreen; color: black; border: 1px solid #CC9999; {self.button_font}')

    def shutdown_menu(self):
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Question)
        msg.setWindowTitle('Shutdown UCATS')
        msg.setText('Stop acquisition and close?')
        msg.addButton('Cancel', QMessageBox.AcceptRole)
        stop_button = msg.addButton('Shutdown', QMessageBox.DestructiveRole)
        msg.exec_()
        if msg.clickedButton() == stop_button:
            if self.instrument is not None:
                self.instrument.shutdown()
            QApplication.instance().quit()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    panel = DisplayPanel(instrument=None)
    panel.setWindowTitle('UCATS Operator Panel (preview)')
    panel.show()
    sys.exit(app.exec_())
