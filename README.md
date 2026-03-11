# SMART COMPOST MONITORING SYSTEM
## Complete User Manual

---

## 1. SYSTEM DESCRIPTION

The Smart Compost Monitoring System is an automated mechatronic system designed to monitor and manage compost piles. It continuously measures:
- **Temperature** (using DHT11 sensor)
- **Gas levels** (using MQ-135 sensor)
- **Soil moisture** (using YL-69 sensor)

When conditions become unfavorable (high temperature or gas), the system automatically activates a cooling fan to maintain optimal composting conditions.

---

## 2. HARDWARE COMPONENTS

### Required Components

| # | Component | Specification | Quantity |
|---|----------|--------------|----------|
| 1 | Arduino UNO R3 | ATmega328P, 16MHz | 1 |
| 2 | DHT11 | Temperature & Humidity Sensor | 1 |
| 3 | MQ-135 | Gas Sensor Module | 1 |
| 4 | YL-69 | Soil Moisture Sensor | 1 |
| 5 | LCD 16x2 | Display with I2C Adapter | 1 |
| 6 | Relay Module | 5V Single Channel | 1 |
| 7 | Cooling Fan | 12V DC | 1 |
| 8 | Power Supply | 12V/2A | 1 |
| 9 | Jumper Wires | Male-Female, Male-Male | 20+ |
| 10 | Breadboard | 400-point | 1 |

---

## 3. PIN CONNECTIONS

### Arduino Pin Mapping

```
┌────────────────────────────────────────────────────────────┐
│                    ARDUINO UNO R3                          │
├────────────────────────────────────────────────────────────┤
│                                                            │
│  DIGITAL PINS:                                             │
│  ────────────                                              │
│  Pin 2  ──────► DHT11 DATA (Yellow/White wire)           │
│  Pin 7  ──────► Relay IN (Control Signal)                │
│  Pin 8  ──────► LCD RS (Register Select)                 │
│  Pin 9  ──────► LCD E (Enable)                            │
│  Pin 10 ──────► LCD D4                                    │
│  Pin 11 ──────► LCD D5                                    │
│  Pin 12 ──────► LCD D6                                    │
│  Pin 13 ──────► LCD D7                                    │
│                                                            │
│  ANALOG PINS:                                              │
│  ───────────                                                │
│  A0  ───────► YL-69 Soil Sensor (Analog Out)             │
│  A1  ───────► MQ-135 Gas Sensor (Analog Out)             │
│                                                            │
│  POWER:                                                    │
│  ──────                                                    │
│  5V  ───────► VCC (All modules)                          │
│  GND ───────► GND (All modules)                          │
│                                                            │
└────────────────────────────────────────────────────────────┘
```

### Detailed Wiring

#### DHT11 Sensor
```
DHT11 Pin    →    Arduino Pin
────────────────────────────────
VCC (Red)    →    5V
GND (Black)  →    GND
DATA (Yellow)→    Digital Pin 2
```

#### MQ-135 Gas Sensor
```
MQ-135 Pin   →    Arduino Pin
────────────────────────────────
VCC          →    5V
GND          →    GND
AOUT         →    Analog Pin A1
```

#### YL-69 Soil Moisture Sensor
```
YL-69 Pin    →    Arduino Pin
────────────────────────────────
VCC          →    5V
GND          →    GND
AOUT         →    Analog Pin A0
```

#### LCD Display (I2C)
```
LCD Pin      →    Arduino Pin
────────────────────────────────
VCC          →    5V
GND          →    GND
SDA          →    A4 (SDA)
SCL          →    A5 (SCL)
```

#### Relay Module
```
Relay Pin    →    Arduino Pin
────────────────────────────────
VCC          →    5V
GND          →    GND
IN           →    Digital Pin 7
```

#### Fan Connection (External 12V)
```
Fan Red Wire   →    Relay COM
Fan Black Wire →    GND
12V Power      →    Relay NO
```

---

## 4. POWER DISTRIBUTION

```
                         12V Power Supply
                              │
                              │
                              ▼
                        ┌──────────┐
                        │   FAN    │
                        └────┬─────┘
                             │
                        ┌────┴────┐
                        │ RELAY   │
                        │  NO     │◄──── 12V+
                        │  COM    │◄──── Fan Red
                        │  NC     │
                        └─────────┘
                              │
                        ┌─────┴─────┐
                        │  Arduino  │
                        │    5V    │
                        └─────┬─────┘
                              │
         ┌──────────┬─────────┼─────────┬──────────┐
         │          │         │         │          │
         ▼          ▼         ▼         ▼          ▼
    ┌────────┐ ┌───────┐ ┌───────┐ ┌────────┐ ┌───────┐
    │ DHT11  │ │ MQ-135│ │ YL-69 │ │  LCD   │ │Relay  │
    │        │ │       │ │       │ │        │ │Module │
    └────────┘ └───────┘ └───────┘ └────────┘ └───────┘
```

---

## 5. SOFTWARE SETUP

### Required Libraries

Install these libraries in Arduino IDE:
1. **DHT.h** - For DHT11 sensor
2. **LiquidCrystal_I2C.h** - For I2C LCD
3. **Wire.h** - For I2C communication (built-in)

### Library Installation

```
Sketch → Include Library → Manage Libraries
Search and install:
- "DHT sensor library" by Adafruit
- "LiquidCrystal I2C" by Frank de Brabander
```

### Arduino Code

Use `Smart_Compost_System.ino` for hardware with I2C LCD.

For Proteus simulation, use `Air_Monitoring_System-/Smart_Compost_Proteus.ino` (parallel LCD).

### Upload Steps

1. Open Arduino IDE
2. File → Open → Smart_Compost_System.ino
3. Select Tools → Board → Arduino UNO
4. Select Tools → Port → COMx
5. Click Upload (→)

---

## 6. SYSTEM OPERATION

### Startup Sequence

1. Power ON → Arduino initializes
2. LCD shows: "SMART COMPOST SYSTEM 19127"
3. 10-second countdown: "READY IN: 10s"
4. Main monitoring loop begins

### Main Loop

```
┌─────────────────────────────────────────┐
│         READ SENSORS                    │
│  - Temperature from DHT11               │
│  - Gas level from MQ-135               │
│  - Soil moisture from YL-69            │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│         CHECK THRESHOLDS                │
│  If Temp > 28°C → FAN ON               │
│  If Gas > 300   → FAN ON               │
│  If Soil > 600  → DRY ALERT            │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│         UPDATE LCD DISPLAY              │
│  - Show temperature                     │
│  - Show gas level                       │
│  - Show status message                  │
│  - Show power status                    │
└────────────────┬────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────┐
│         DELAY 2 SECONDS                 │
│         REPEAT LOOP                     │
└─────────────────────────────────────────┘
```

---

## 7. THRESHOLD CONFIGURATION

### Default Values

| Parameter | Threshold | Description |
|-----------|-----------|-------------|
| Temperature | 28°C | Fan activates above this |
| Gas Level | 300 | Fan activates above this (0-1023 scale) |
| Soil Moisture | 600 | DRY alert above this (0-1023 scale) |

### Modifying Thresholds

In the Arduino code, find and modify:

```cpp
const float TEMP_TRIGGER = 70.0;  // Change temperature threshold
const int GAS_TRIGGER = 300;       // Change gas threshold
const int SOIL_DRY_LIMIT = 60%;   // Change soil threshold
```

---

## 8. LCD DISPLAY MESSAGES

### Status Messages

| Message | Meaning | Action |
|---------|---------|--------|
| HOT! | Temperature > 70°C | Fan turns ON |
| GAS! | Gas level > 300 | Fan turns ON |
| DRY! | Soil moisture > 60% | No fan action |
| DEC OPT | All parameters normal | Fan is OFF |
| PWR:ON | Fan is running | - |
| PWR:OFF | Fan is stopped | - |

### Sample Display

```
Line 1: T:25C G:150    
Line 2: DEC OPT |PWR:OFF
```

### Proteus Wiring

Follow the complete wiring guide in `PROTEUS_WIRING_DIAGRAM.md`

### Loading Arduino HEX File

1. Compile Arduino code: Sketch → Export Compiled Binary
2. In Proteus, double-click Arduino UNO
3. Click folder icon next to "Program File"
4. Browse to the .hex file
5. Click OK and run simulation

### Testing Scenarios

| Scenario | Setting | Expected Result |
|----------|---------|-----------------|
| Normal | Temp < 69°C, Gas < 299 | DEC OPT, PWR:OFF |
| High Temp | Temp > 70°C | HOT!, PWR:ON |
| High Gas | Gas > 300 | GAS!, PWR:ON |
| Dry Soil | Soil > 60% | DRY!, PWR:OFF |

---

## 10. TROUBLESHOOTING

### Common Issues

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| LCD shows nothing | No power or contrast | Check 5V connection, adjust contrast |
| LCD shows black boxes | Initialization failed | Check I2C address (0x27) |
| Temperature shows NaN | DHT11 not connected | Check Pin 2 connection |
| Gas value always high | Sensor not warmed up | Allow 24hr preheat |
| Relay not switching | Active-low confusion | Check IN pin signal |
| Fan not running | External 12V missing | Check power supply |

### Testing Individual Sensors

```cpp
// Test DHT11
float t = dht.readTemperature();

// Test Gas (analog reading)
int gas = analogRead(A1);

// Test Soil (analog reading)
int soil = analogRead(A0);
```

---

## 11. TECHNICAL SPECIFICATIONS

### Power Requirements
- Arduino: 5V via USB or barrel jack
- Sensors: 5V (total ~200mA)
- Fan: 12V DC (~200mA)
- Total system: 12V/1A recommended

### Sensor Ranges
- DHT11 Temperature: 0-50°C (±2°C)
- DHT11 Humidity: 20-90% RH (±5%)
- MQ-135: 10-1000 ppm (for CO2)
- YL-69: 0-1023 (analog)

### Operating Conditions
- Temperature: 0-50°C
- Humidity: 10-90% (non-condensing)

---

## 12. SAFETY PRECAUTIONS

1. Always disconnect power before wiring
2. Use proper voltage ratings (5V for sensors, 12V for fan)
3. Do not exceed Arduino current limits
4. Keep sensors away from water immersion
5. Ensure fan is properly ventilated

---

## 13. FILES IN THIS PROJECT

| File | Description |
|------|-------------|
| Smart_Compost_System.ino | Main Arduino code (I2C LCD) |
| Smart_Compost_Proteus.ino | Proteus-compatible code (parallel LCD) |


---

## 14. SUPPORT

For issues or questions:
- Check wiring connections
- Verify code compiles without errors
- Ensure correct COM port selected
- Check power supply voltages

---

## 15. CREDITS

**Developers:
- Dennis Muthuri Mwathe

**Supervisor:**
- Stephanie Masika
