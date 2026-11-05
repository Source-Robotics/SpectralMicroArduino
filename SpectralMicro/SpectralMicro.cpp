#include "SpectralMicro.h"

SerialCommandLibrary::SerialCommandLibrary(HardwareSerial& serialPort) : _serialPort(serialPort) {}

void SerialCommandLibrary::begin(long baudRate) {
    _serialPort.begin(baudRate);
}

void SerialCommandLibrary::KV(float value) {
    sendCommand("#KV " + String(value, 6));
}

void SerialCommandLibrary::L(float value) {
    sendCommand("#L " + String(value, 6));
}

void SerialCommandLibrary::R(float value) {
    sendCommand("#R " + String(value, 6));
}

void SerialCommandLibrary::Cal() {
    sendCommand("#Cal");
}

void SerialCommandLibrary::sendCommand(const String& command) {
    _serialPort.print(command + "\r\n");
}

void SerialCommandLibrary::loop() {
    while (_serialPort.available()) {
        String received = _serialPort.readStringUntil('\n');
        Serial.println("Received: " + received);
    }
}
