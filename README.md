# Home Automation System 

This repository contains the source code, hardware architecture, and documentation for a Home Automation System developed during an Embedded Systems and Design internship at Maven Silicon.

## Overview

This project automates lighting and fan control based on real-time environmental conditions and presence detection. It leverages NodeMCU (ESP8266) with WiFi capabilities, DHT11 temperature sensor, LDR, and an ultrasonic sensor to optimize comfort, safety, and energy efficiency in home environments. Manual override is provided through the Blynk mobile app for remote control.

## Features

### Functional Requirements
- *Automatic Light Control*
  - Uses LDR and ultrasonic sensor to detect darkness and presence.
  - Turns ON the bulb when a person is present and it's dark.
  - Turns OFF the bulb when the room is empty.

- *Automatic Fan Control*
  - Uses DHT11 to monitor temperature.
  - Turns ON the fan when temperature exceeds 60°C and someone is present.
  - Turns OFF the fan when temperature is normal or no one is present.

- *Manual Mode*
  - Remote control via Blynk mobile app.
  - Allows turning ON/OFF the fan and bulb.
  - Manual and Auto modes are mutually exclusive.

- *WiFi Connectivity*
  - NodeMCU connects to home WiFi for remote access.

## Hardware Components

| Component             | Quantity | Description                                      |
|-----------------------|----------|--------------------------------------------------|
| NodeMCU ESP8266       | 1        | Microcontroller with built-in WiFi               |
| DHT11 Sensor          | 1        | Measures room temperature                        |
| LDR Sensor            | 1        | Detects ambient light level                      |
| Ultrasonic Sensor     | 1        | Detects human presence based on distance         |
| 2-Channel Relay Module| 1        | Controls high-voltage devices                    |
| Light Bulb            | 1        | Connected via relay for automation               |
| Fan                   | 1        | Connected via relay for automation               |
| Jumper Wires          | 40       | For connecting all components                    |

## Software Architecture

- Code written in C++ using Arduino IDE.
- Main functions:
  - setup(): Initializes sensors, relays, and WiFi.
  - loop(): Handles control logic (manual or automatic).
  - handleAutoMode(): Logic for automatic control.
  - handleManualMode(): Blynk-based control from mobile.
- Blynk integration for mobile app interface.

## Mobile App

The project integrates with [Blynk](https://blynk.io/) for remote control. You can:
- Toggle between Auto and Manual mode.
- Manually control fan and light in Manual mode.
- Monitor system status via mobile.

## Testing

- Unit testing of individual sensors and relays.
- Integration testing of sensor-triggered automation.
- System testing in real-world room conditions.
- Verified timing constraints (response within 1 minute).

## Future Work

- Integrate with Alexa or Google Assistant for voice control.
- Add air quality and CO₂ sensors.
- Enhance UI with custom automation rules and stats.
- Predictive maintenance and ML-based optimization.

## Documentation

Detailed project documentation is available in 21BEC1214_HOME_AUTOMATION_REPORT.pdf.

## Author

*Aditi Srivastava*  
Vellore Institute of Technology, Chennai  
Intern at Maven Silicon  
Registration No: 21BEC1214

## Submission Date

11 July 2024

---
