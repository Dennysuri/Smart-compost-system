# Smart Compost Monitoring System

## Project Overview

The Smart Compost Monitoring System is an automated monitoring solution for compost management. It continuously monitors temperature, gas levels, and soil moisture, automatically activating cooling mechanisms when necessary.

## System Components

| Component | Description | Quantity |
|-----------|------------|----------|
| Arduino UNO R3 | Microcontroller | 1 |
| DHT11 | Temperature & Humidity Sensor | 1 |
| MQ-135 | Gas Sensor | 1 |
| YL-69 | Soil Moisture Sensor | 1 |
| 16x2 LCD | Display | 1 |
| 5V Relay Module | Fan Control | 1 |
| 12V Fan | Cooling | 1 |

## Pin Configuration

| Arduino Pin | Component |
|-------------|-----------|
| Pin 2 | DHT11 Data |
| Pin 7 | Relay IN (Fan Control) |
| Pin 8 | LCD RS |
| Pin 9 | LCD E |
| Pin 10 | LCD D4 |
| Pin 11 | LCD D5 |
| Pin 12 | LCD D6 |
| Pin 13 | LCD D7 |
| A0 | Soil Moisture Sensor |
| A1 | Gas Sensor |

## Threshold Values

| Parameter | Threshold | Action |
|-----------|-----------|--------|
| Temperature | 60°C | Fan ON if > 70°C |
| Gas Level | 300 | Fan ON if > 300 |
| Soil Moisture | 60% | Display DRY if > 80% |

## Status Messages

- **HOT!** - Temperature too high
- **GAS!** - Gas level too high
- **DRY!** - Soil too dry
- **DEC OPT** - Decomposition Optimized (all good)
- **PWR:ON/OFF** - Fan power status

## Files

- `Smart_Compost_System.ino` - Main Arduino code (I2C LCD version)
-  Smart_Compost_Proteus.ino` - Proteus-compatible code (parallel LCD)
- `PROTEUS_WIRING_DIAGRAM.md` - Complete wiring guide for Proteus simulation
- `Smart_Compost_Monitoring_System_Project_Paper.md` - Full project documentation

## How to Use

1. **Hardware**: Connect components according to the pin configuration
2. **Software**: Upload the appropriate Arduino sketch
3. **Proteus Simulation**: Use PROTEUS_WIRING_DIAGRAM.md for simulation setup

## Arduino Code

The main code reads sensors and controls the fan:
- Reads temperature from DHT11
- Reads gas level from MQ-135 (analog)
- Reads soil moisture from YL-69 (analog)
- Activates fan when temperature > 28°C or gas > 300
- Displays status on LCD

## Credits

- Dennis Muthuri Mwathe
- Supervisor: Masika

