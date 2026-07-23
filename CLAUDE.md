# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository overview

This repo holds instrument-control software for UCATS, a NOAA/GML airborne 3-channel ECD gas chromatograph (custom electrometer detectors, Valco valves, Omega temperature controllers, ADR2000 analog/digital I/O). UCATS previously carried other instruments (H2O, ozone, TDL) alongside the GC — those are physically removed from the instrument now; UCATS is simply a 3-channel ECD GC. It has three layers:

- `drivers/` and `flight/` — the legacy QNX Neutrino C source tree ("PANTHER" flight software) that actually ran on the instrument's QNX flight computer. Reference/legacy only — not buildable here. `flight/` is the current 3-channel-GC version of this tree (VERSION 3.1, dated 2023-03-01); an older 2-channel version is kept alongside it as `flight-2016/` for reference/diffing. `flight/`'s C source still contains code for the removed legacy sensors (ozone.tmc, h2oext, vaisala.tmc, etc., still referenced by `flight/src/Makefile`) — that's leftover from the not-yet-pruned legacy tree, not a sign those sensors are still present; don't port it.
- Top-level driver modules (`adr2000.py`, `omega.py`, `smart.py`, `valco.py`, `autodetect.py`, `scheduler.py`) — Python 3 translations of the C drivers, meant to run standalone (off the QNX box).
- `ucats.py` + `config.yaml`/`setup.yaml` + `display.py`/`display_panel.py`/`telemetry.py` — a new standalone Python acquisition system built to replace the QNX flight software entirely, described below.

There is no test suite, lint config, or CI in this repo. Devices can't be exercised without hardware yet — there is no `sim_mode` (unlike sibling repos ucats-b/FE3_acquisition) — so verification here has meant unit-testing individual methods against fake hardware objects (see git history / recent sessions for the pattern) rather than running the real acquisition loop.

## The new acquisition system (`ucats.py`)

`ucats.py`'s `Instrument_UCATS` orchestrates the whole instrument: valve/injection sequencing, electrometer polling + ITX chromatogram output, Omega temperature monitoring, ADR2000 solenoid/analog I/O, engineering data logging, and telemetry. Run it with `python3 ucats.py` (launches the PyQt5 GUI by default) or `python3 ucats.py --headless` (no GUI, starts acquisition immediately).

It's modeled on two sibling repos, deliberately mixing their patterns rather than copying one wholesale:
- **`../FE3_acquisition`** (`fe3.py`/`gc7890.py`/`scheduler.py`/`valco.py`) — for the GC/valve/scheduler/ITX-output shape. `scheduler.py` and `valco.py` here are near-verbatim ports; `smart.py`'s `GCChannels`/`GCChannel` classes replace `gc7890.py`'s continuous-stream model because the smart electrometer has no stream — it's polled once/sec and returns up to 16 buffered points per poll (`MAXPOINTS` in `smart.h`; see `flight/gc.tmc`'s `GC_Ctr_Pull`).
- **`../ucats-b`** (`instrument.py`/`display_panel.py`/`telemetry.py`) — for the per-tick collect/merge/telemetry loop and the operator-panel GUI shape. `telemetry.py` is a near-verbatim port. UCATS has no flask sampling (unlike FE3), so none of FE3's flask-UI machinery (barcode scanner, cal tank tables, manifold pump-down) was ported.

Two YAML config files, split by how often they change (mirrors FE3's `fe3_config.py`/`setup.py` split, converted to YAML):
- **`config.yaml`** — hardware addresses/ports, paths, the `mode` setting (see below). Rarely edited.
- **`setup.yaml`** — chromatogram duration, injection ratio, backflush/solenoid timing, flow/pressure setpoint programs. Edited per run/deployment.

### Provenance convention — read this before touching config.yaml/setup.yaml

Every value in these two files is either **confirmed** (cross-referenced against a specific file in `flight/src/`, cited in an adjacent comment) or marked **`TODO`** (a placeholder, not to be trusted). Do not silently replace a `TODO` with a guessed value — either find it in the legacy source or leave the placeholder. Sources mined so far, in case more values are needed later:

| File | Gave us |
|---|---|
| `flight/src/addresses.h` | electrometer/GSV/cal-SSV addresses (3 channels: `CH1elecADD`/`CH2elecADD`/`CH3elecADD`) |
| `flight/src/uav.tma` | startup sequence timing, air:cal injection ratio (4:1), detector-ready temp thresholds, N2 failsafe (confirmed disabled — see `setup.yaml`'s `carrier_gas`), pump pressure thresholds |
| `flight/src/uav.sol` | the *real* chromatogram sequence and per-second solenoid/valve/GSV/backflush timing. `uav.sol` defines several routines (70s/140s/280s variants); the one actually run in flight is mode 2 ("RUN mode") → mode 22 → `chrom140s_A` immediately followed by `chrom140s_B`, repeating (`chrom70s_A`/`chrom280s_*` are lab-only, not used). Each block is 75 real seconds (15 groups × 5 chars, `resolution = 1/1` = 1 char = 1s) despite the "140s" name. ch2/ch3 complete a full inject/backflush cycle every block; ch1's column needs both blocks (150s) to separate, so its GSV only injects on the "A" block and stays in Load through "B" — see `setup.yaml`'s `chromduration`/`gsv_phase_channels` notes and `ucats.py`'s `self.gsv_phase`. Format: 5-char groups separated by `:` |
| `flight/src/uav.slp` | the numeric setpoint for each lettered stage referenced in `uav.sol` (flow/pressure values) |
| `flight/src/analog.tmc` | ADR2000 DAC calibration formulas and board/channel addressing for flow/pressure setpoints (3 channels; note channel 3's backflush-pressure DAC isn't wired yet — its `pres_BP3_sp` line is commented out) |
| `flight/src/omega.tmc` | real Omega temperature controller addresses (7 zones now — 3 channels, but only channel 3 has a post-column zone; the old water-trap Peltier heater zone, `h2o_pelt`, is gone along with the physical H2O sensor) |
| `flight/src/digital.tmc` | real ADR2000 digital channel numbers. Use `flight/src/digital.tmc` itself, not the `flight/src/digital_230301.tmc` file alongside it — despite the name, `digital_230301.tmc` is the *older* (2022-05-11) file matching `flight-2016`'s addresses; `digital.tmc` (2023-03-01) is what `flight/src/Makefile` actually builds and has the current addresses. Same caveat applies to `hardware_230301.cfg` vs. `hardware.cfg`. Also gave us the `pump`/`nitrogen`/`heartbeat` dig channels (board/channel confirmed, but not yet driven automatically — see `setup.yaml`'s `startup_sequence` note and `ucats.py`'s `_heartbeat_pulse()`). |
| `flight/src/uav.cmd` | the grammar mapping `uav.tma`'s `> action` lines to real hardware commands. Confirmed channel 3's GSV has **inverted** position polarity vs. ch1/ch2 (`&GSVVALVEPOS_Inv`: Inject=position B, Load=position A) — a real plumbing difference, not a typo (`drivers/valve/valco.c`'s `switch_valve()` treats every valve ID identically, so the inversion is channel-3-specific wiring). See `config.yaml`'s `gc_channels[2].gsv_inverted` and `valco.py`'s `GSV(inverted=...)`. Also the source for the `SOLDRV_A` architecture note above, and for `elec bias`/`elec reset` mapping to `smart.py`'s `change_dac()`/`send_reset()` (see `setup.yaml`'s `electrometer_bias`, sourced from `uav.slp`'s `Proxy elecCH1/2/3` blocks). |

### Flight vs. calibration mode

Air/cal switching hardware differs by deployment, per `config.yaml`'s `mode` setting:
- **`flight`** (default) — a 2-position digital solenoid on the ADR2000 (`devices.adr2000.dig.ssv`), what's actually connected on the aircraft.
- **`calibration`** — an external multi-position Valco SSV (`ssv.cal_add`), only physically hooked up in the lab for GC calibration.

`Instrument_UCATS.select_air_cal()`/`current_selpos()` dispatch on `self.mode`; `set_mode()` switches at runtime (lazily connecting the Valco SSV) and is wired to the GUI's calibration-mode toggle button in `display_panel.py`.

### SOLDRV_A: `ucats.py`'s scheduler replaces a hardware board, not just software

In the legacy QNX design, the second-by-second GSV/backflush/flow timing in `flight/src/uav.sol` did **not** run on the main flight-logic process. It ran autonomously on a separate real-time process/board called SOLDRV_A: `flight/src/uavcmd.c` loads `uav.sol`'s compiled program into it via `solp_init(SOLDRV_PROXY_A, ...)` calls, `flight/src/uav.cmd`'s `Mode &ModeSet` sends it a single mode-select command (`send_dascmd(DCT_SOLDRV_A, ...)`, e.g. mode 2 = "GC Run"), and `flight/src/basecol.tmc` reads its `GCstate` back via a shared-memory pointer ("magic number 4 for SOLDRV_A"). `flight/src/uav.tma`'s state machine never calls the per-second solenoid/flow commands itself — SOLDRV_A does, in its own hardware/firmware timing loop, once told which mode to run.

`ucats.py` has no SOLDRV_A driver (none exists anywhere in this repo) and doesn't send a mode-select command to one. Instead — confirmed intentional, not an oversight, per `ucats.py`'s own module docstring — `Instrument_UCATS` reimplements that entire timing role itself in Python: `_schedule_injection_timing()` queues each GSV switch/flow ramp/solenoid event as a `scheduler.py` task timed from `setup.yaml`'s per-second data (itself extracted from `uav.sol`/`uav.slp`). This is the right architecture for "replace the QNX flight software entirely," but it means chromatogram timing precision now depends on a Python `threading`-based scheduler on a general-purpose OS instead of a dedicated real-time board. If retention times or peak shapes drift or jitter during hardware testing compared to what the legacy system produced, this is the first place to look — measure `scheduler.py`'s actual dispatch latency under load (electrometer polling + telemetry + GUI all competing) before assuming a wiring/config error.

### History: the 2016→2023 flight source update

`flight/` used to describe a 2-channel GC; that older tree is preserved as `flight-2016/` for reference/diffing. The current `flight/` tree (VERSION 3.1, 2023-03-01) is a 3-channel GC — `config.yaml`/`setup.yaml`/`ucats.py` were updated accordingly (`gc_channels`/`GCChannels`/the DAC/dig configs all cover `ch1`/`ch2`/`ch3`). A good number of values also *changed*, not just gained a third channel — e.g. the air:cal injection ratio (7:1 → 4:1), pump pressure thresholds (~1000/950 mbar → 450/400 mbar), flow/pressure DAC calibration curves (`analog.tmc`'s `SCCMsp`/`PSIsp` typedefs were replaced by `SCCMspPN`/`PSIBspPN` with different slope/intercept), and the N2 carrier-gas failsafe (now commented out in `uav.tma`, confirmed disabled). See `config.yaml`/`setup.yaml`'s inline comments for the full diff against `flight-2016`, cited value by value.

`setup.yaml`'s chromatogram timing was initially (incorrectly) derived from `uav.sol`'s `chrom70s_A` routine, a lab-only mode (mode 3). The real flight sequence is mode 2 → `chrom140s_A`/`chrom140s_B` back to back — see the `uav.sol` provenance row above and `setup.yaml`'s `chromduration` note for the corrected model (75s/cycle, with ch1's GSV alternating an 'A'/'B' phase since its column needs two cycles to separate).

Some `TODO`s remain unresolved by this update (cal/ambient SSV port numbers, the digital-solenoid polarity, DAC board/channel inferences in `analog.tmc`'s encoding, channel 3's still-unwired backflush-pressure DAC) — if a further-updated `flight/` tree ever lands, diff it against the current one the same way this update diffed `flight/` against `flight-2016/`: cite the source file for every changed value, don't assume unchanged values still apply as-is.

## Running the Python driver scripts

- No build step; run directly, e.g. `python3 adr2000.py -h`, `python3 smart.py -h`, `python3 omega.py -h`, `python3 valco.py -h`.
- Each script's argparse `-h`/`--help` documents its full CLI, including usage examples in the epilog.
- `python3 display_panel.py` / `python3 display.py` give a UI-only preview with fake data, no hardware or full `Instrument_UCATS` needed.
- Third-party deps: `pyserial` (imported as `serial`), `numpy`, `pyyaml`, `pandas`, `PyQt5`, `matplotlib`. No `requirements.txt` exists — install manually.
- `omega.py --config <address>` loads PID parameters for that controller address from `omega_config.yaml` (columns map to Omega commands W503/W504/W505 = P/I/D) and writes them to the controller.

## Python driver architecture

Each low-level driver module is a translation of the matching C driver in `drivers/<name>/<name>.c`, adapted to standalone CLI use, and they follow a consistent pattern — use `adr2000.py` or `smart.py` as the template for any new one:

- A class wraps a `pyserial` `Serial` connection and implements the device's wire protocol as methods (checksum framing, command bytes, response parsing) that mirror the C functions 1:1. For example `smart.py`'s `send_command`/`parse_chrom` reproduce `smart.c`'s functions of the same name, including its exact (slightly quirky) checksum math — when translating, preserve that fidelity rather than "fixing" apparent bugs.
- `if __name__ == '__main__':` builds an argparse CLI whose flags mirror the original C driver's `getopt` options (see each driver's `usage()`/`init_opt()` in the `.c` file), so behavior stays recognizable to people who used the C tool. Prefer argparse's built-in `-h/--help` (with `epilog` + `RawDescriptionHelpFormatter` for usage examples) over hand-rolling a `usage()` function.
- The QNX-specific parts of the C drivers (message passing via `Creceive`/`Col_send`/proxies, `qnx_name_attach`) have no meaning outside QNX and are not translated. Where the C driver ran forever as a background IPC server, the Python version substitutes a plain polling loop, a `scheduler.py`-driven task, or a one-shot command mode instead.
- `autodetect.py`'s `SerialAutoDetect` handles port autodetection for `valco.py`/`omega.py`/`adr2000.py`; baud rates there must match each real driver (`drivers/valve/valco.c`, `drivers/adr2000/adr2000.c` = 9600, Omega Platinum Series = 19200) rather than assumptions carried over from sibling repos. `smart.py` has no autodetect dependency (fixed port, like the C original).
- `hardware.cfg` (line format `<driver>: <key>: <value...>`) is a legacy QNX config format, still read by `smart.py`'s CLI polling-loop mode; `ucats.py` does not use it — `config.yaml`'s `gc_channels` list replaced that role for the new orchestrator.

## C driver tree (`drivers/`, `flight/`)

- Each `drivers/<name>/` is a standalone QNX driver: `<name>.c`, `<name>.h`, a `Makefile` (`CC=cc`, QNX-only), and a compiled binary — not buildable on non-QNX systems.
- Each Makefile's `install` target copies the binary to `/home/uav/bin` and the header to `/home/uav/flight/src` — these paths only exist on the real flight computer.
- `flight/` is the full QNX flight-software tree that builds and runs the instrument (`.tmc`/`.tma`/`.doit`/`.fld`/`.sol`/`.slp` files, driven by `flight/src/Makefile`), also QNX-only. The `.tmc`/`.tma`/`.sol`/`.slp` files are plain text and worth reading directly (`grep`/`Read`) when hunting for real hardware addresses, timing, or calibration data — several were mined this way for `config.yaml`/`setup.yaml` (see the provenance table above). `flight-2016/` is the same kind of tree, one generation older — useful for diffing what changed (see "History" above), otherwise superseded.
- Treat `drivers/`, `flight/`, and `flight-2016/` as reference/legacy source when translating protocols to Python — not something to build or run from this repo's environment.
