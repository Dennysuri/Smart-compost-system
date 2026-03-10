# Smart Compost Monitoring System - Electrical Design

## System Wiring (Point-to-Point)

### Power Distribution

**Power Hub (5V):** A single wire from Arduino 5V is split into 5 branches using a soldered/twisted splice to power the DHT11, MQ-135, Soil Sensor, LCD, and Relay.

**Common Ground (GND):** All component Ground wires are tied together into a central "Ground Rail" returning to the Arduino GND pin.

---

### Sensor Connections

| Sensor | Pin Connection |
|--------|----------------|
| DHT11 (Temperature/Humidity) | Digital Pin 2 |
| MQ-135 (Gas Sensor) | Analog Pin A1 |
| Soil Moisture Sensor | Analog Pin A0 |

---

### Actuator (Fan) Control

- **Control Signal:** Digital Pin 7 triggers the Relay IN pin
- **Load Power:** The Fan is powered by an external 12V source, with the Positive lead passing through the Relay's Normally Open (NO) and Common (COM) terminals

---

### Component List

1. Arduino Uno
2. DHT11 Temperature & Humidity Sensor
3. MQ-135 Gas Sensor
4. Soil Moisture Sensor
5. I2C LCD Display (16x2)
6. 5V Relay Module (Active Low)
7. 12V Fan (External Power)
8. Jumper Wires
9. Power Supply (12V for Fan, 5V from Arduino)

---

### Wiring Notes

- All sensors use the 5V power from Arduino
- The relay uses an active-low configuration (HIGH = OFF, LOW = ON)
- Point-to-point wiring eliminates need for a breadboard
- Ground rails are consolidated for clean circuit design

