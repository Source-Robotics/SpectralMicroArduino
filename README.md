# SpectralMicroArduino

**Arduino library to control the Spectral Micro BLDC controller from an Arduino board, over UART.** It sends the
driver's text commands from a hardware serial port: set KV, L and R, start a calibration, and print what the driver
answers.

[Documentation](https://docs.source-robotics.com/Spectral-BLDC-docs/latest/06-operation/uart/) ·
[Download](https://github.com/Source-Robotics/SpectralMicroArduino/releases/latest) ·
[Examples](https://github.com/Source-Robotics/SpectralMicroArduino/tree/main/SpectralMicro/Examples) ·
[Discord](https://discord.com/invite/prjUvjmGpZ)

[![Release](https://img.shields.io/github/v/release/Source-Robotics/SpectralMicroArduino?style=flat-square&color=143952&label=release)](https://github.com/Source-Robotics/SpectralMicroArduino/releases/latest)
[![Platform](https://img.shields.io/badge/platform-Arduino-143952?style=flat-square)](https://github.com/Source-Robotics/SpectralMicroArduino#install)
[![License](https://img.shields.io/badge/license-MIT-143952?style=flat-square)](https://github.com/Source-Robotics/SpectralMicroArduino/blob/main/LICENSE)
[![Discord](https://img.shields.io/discord/1072498136284667955?style=flat-square&logo=discord&logoColor=white&label=discord&color=292B37)](https://discord.com/invite/prjUvjmGpZ)

> [!NOTE]
> Early stage: the library has four of the driver's commands so far. Updated UART commands, CAN support and more
> examples are on the [to-do list](https://github.com/Source-Robotics/SpectralMicroArduino#to-do).

## Install

The library is not in the Arduino Library Manager. Download the repository and copy its `SpectralMicro` folder
into your Arduino `libraries` folder (on Windows `Documents\Arduino\libraries`):

```
git clone https://github.com/Source-Robotics/SpectralMicroArduino.git
```

You need a board with a free hardware serial port (the library takes a `HardwareSerial`), tested with the Teensy
4.1, wired to the driver's UART connector, a 4-pin JST SH (3V3, GND, TX, RX; the
[UART cable](https://source-robotics.com/products/uart-cable) has it on both ends). Cross TX and RX, the driver's
TX to the board's RX and the driver's RX to the board's TX, and connect GND. The driver's UART is 3.3 V and runs at
256000 baud by default; 5 V destroys the board, so use a 3.3 V board or a level shifter
([Connectors and pinout](https://docs.source-robotics.com/Spectral-BLDC-docs/latest/03-technical-data/connectors/)).

## Quick start

On a Teensy 4.1, `Serial1` (pins 0 and 1) goes to the driver and the USB serial port shows what it answers:

```cpp
// Tested on Teensy 4.1 with Spectral Micro
// Use serial1 for communication with the Spectral Micro and usb serial for debugging
// Teensy 4.1 has Serial1 on pins 0 and 1, which are the RX and TX pins respectively
#include <SpectralMicro.h>

SerialCommandLibrary mySerial(Serial1);

void setup() {
    Serial.begin(256000);
    mySerial.begin(256000);
    delay(1000); // Give some time for the serial connection to establish

    // Example commands
    mySerial.KV(0.123);
    mySerial.L(1.234);
    mySerial.R(2.345);
    mySerial.Cal();
}

void loop() {
    Serial.println("testing");
    mySerial.loop(); // Continuously check for incoming data
    delay(1000); // once a second
}
```

What each command does and answers: the [UART reference](https://docs.source-robotics.com/Spectral-BLDC-docs/latest/reference/uart/)
in the Spectral Micro manual.

## Works with

| Product | Firmware | Repository |
|---|---|---|
| Spectral Micro BLDC controller | 101 to 107 (the four commands are the same in each) | [Spectral-Micro-BLDC-controller](https://github.com/Source-Robotics/Spectral-Micro-BLDC-controller) |

Tested with a Teensy 4.1. The STEPFOC stepper controller's firmware 108 has the same four UART commands; the
library has not been tested with it. Which firmware your driver runs: the compatibility pages of the
[Spectral Micro](https://docs.source-robotics.com/Spectral-BLDC-docs/latest/appendix/compatibility/) and
[STEPFOC](https://docs.source-robotics.com/STEPFOC-docs/latest/appendix/compatibility/) manuals.

## Examples

In [SpectralMicro/Examples](https://github.com/Source-Robotics/SpectralMicroArduino/tree/main/SpectralMicro/Examples):

| Example | What it does |
|---|---|
| `example.ino` | the quick start above, on a Teensy 4.1: opens `Serial1` to the driver at 256000 baud, sets KV, L and R and starts a calibration, then every second prints `testing` and every line the driver sent |

## API reference

The class `SerialCommandLibrary`, in `SpectralMicro.h`:

| Call | What it does |
|---|---|
| `SerialCommandLibrary(HardwareSerial& serialPort)` | the serial port wired to the driver, for example `Serial1` |
| `begin(long baudRate)` | opens the port; the driver's default is 256000 |
| `KV(float value)` | sends `#KV <value>`: sets the velocity constant, in rpm/V |
| `L(float value)` | sends `#L <value>`: sets the phase inductance, in H |
| `R(float value)` | sends `#R <value>`: sets the phase resistance, in Ω |
| `Cal()` | sends `#Cal`: runs the driver's calibration; it measures R and L, finds the pole pairs, the phase order and the angle offset, and measures Kt, KV and the flux linkage |
| `loop()` | prints every line the driver sent on the USB serial port (`Serial`), as `Received: <line>` |

Each command ends with CR LF. The value is written with six decimals (`String(value, 6)`), so an inductance such as 0.0004 H arrives whole.

## To do

* Update uart commands
* Add CAN support
* Examples

## Community

Ask in [Discussions](https://github.com/orgs/Source-Robotics/discussions), chat on
[Discord](https://discord.com/invite/prjUvjmGpZ), report a bug in
[Issues](https://github.com/Source-Robotics/SpectralMicroArduino/issues). Follow Source Robotics:

[![Discord](https://img.shields.io/discord/1072498136284667955?style=flat-square&logo=discord&logoColor=white&label=discord&color=143952)](https://discord.com/invite/prjUvjmGpZ)
[![Discussions](https://img.shields.io/badge/discussions-ask_a_question-143952?style=flat-square&logo=github&logoColor=white)](https://github.com/orgs/Source-Robotics/discussions)
[![YouTube](https://img.shields.io/badge/youtube-%40source--robotics-143952?style=flat-square&logo=youtube&logoColor=white)](https://www.youtube.com/@source-robotics)
[![Instagram](https://img.shields.io/badge/instagram-%40source__robotics-143952?style=flat-square&logo=instagram&logoColor=white)](https://www.instagram.com/source_robotics/)
[![X](https://img.shields.io/badge/x-%40SourceRobotics-143952?style=flat-square&logo=x&logoColor=white)](https://x.com/SourceRobotics)
[![LinkedIn](https://img.shields.io/badge/linkedin-Source_Robotics-143952?style=flat-square&logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyNCAyNCI%2BPHBhdGggZmlsbD0id2hpdGUiIGQ9Ik0yMC40NDcgMjAuNDUyaC0zLjU1NHYtNS41NjljMC0xLjMyOC0uMDI3LTMuMDM3LTEuODUyLTMuMDM3LTEuODUzIDAtMi4xMzYgMS40NDUtMi4xMzYgMi45Mzl2NS42NjdIOS4zNTFWOWgzLjQxNHYxLjU2MWguMDQ2Yy40NzctLjkgMS42MzctMS44NSAzLjM3LTEuODUgMy42MDEgMCA0LjI2NyAyLjM3IDQuMjY3IDUuNDU1djYuMjg2ek01LjMzNyA3LjQzM2MtMS4xNDQgMC0yLjA2My0uOTI2LTIuMDYzLTIuMDY1IDAtMS4xMzguOTItMi4wNjMgMi4wNjMtMi4wNjMgMS4xNCAwIDIuMDY0LjkyNSAyLjA2NCAyLjA2MyAwIDEuMTM5LS45MjUgMi4wNjUtMi4wNjQgMi4wNjV6bTEuNzgyIDEzLjAxOUgzLjU1NVY5aDMuNTY0djExLjQ1MnpNMjIuMjI1IDBIMS43NzFDLjc5MiAwIDAgLjc3NCAwIDEuNzI5djIwLjU0MkMwIDIzLjIyNy43OTIgMjQgMS43NzEgMjRoMjAuNDUxQzIzLjIgMjQgMjQgMjMuMjI3IDI0IDIyLjI3MVYxLjcyOUMyNCAuNzc0IDIzLjIgMCAyMi4yMjIgMGguMDAzeiIvPjwvc3ZnPg%3D%3D)](https://www.linkedin.com/company/source-robotics/)
[![Blog](https://img.shields.io/badge/blog-source--robotics.com-143952?style=flat-square&logo=rss&logoColor=white)](https://source-robotics.com/blogs/blog)

## Safety, liability and disclaimer

1. The software and hardware are still in development and may contain bugs, errors, or incomplete features.
2. Users are encouraged to use this software and hardware responsibly and at their own risk.

Read the manual's [safety chapter](https://docs.source-robotics.com/Spectral-BLDC-docs/latest/02-safety/) before you wire and power the driver.

## Licensing

Project is under [MIT Licence](https://github.com/Source-Robotics/SpectralMicroArduino/blob/main/LICENSE)
