/*
 * Project: Smart Mechatronic Compost Monitoring System
 * Author: Dennis Muthuri Mwathe (19127)
 * Hardware: Arduino Uno, DHT11, MQ-135, Soil Moisture, I2C LCD, 5V Relay
 * Goal: Accelerated Manure Production for Farmers (SDG 2, 9, 11, 12, 13)
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2          
#define DHTTYPE DHT11     
#define RELAY_PIN 7       
#define SOIL_PIN A0       
#define GAS_PIN A1        

const float TEMP_TRIGGER = 28.0;  
const int GAS_TRIGGER = 300;      

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Default OFF (Active Low Relay)

  dht.begin();
  lcd.init();
  lcd.backlight();

  // Initialization Sequence
  lcd.print(" SMART COMPOST ");
  lcd.setCursor(0, 1);
  lcd.print(" SYSTEM 19127  ");
  delay(3000); 

  lcd.clear();
  for(int i = 10; i > 0; i--) {
    lcd.setCursor(0, 0);
    lcd.print("INITIALIZING...");
    lcd.setCursor(0, 1);
    lcd.print("READY IN: "); lcd.print(i); lcd.print("s ");
    delay(1000); 
  }
  lcd.clear();
}

void loop() {
  float t = dht.readTemperature();
  int gas = analogRead(GAS_PIN);
  int soil = analogRead(SOIL_PIN);

  if (isnan(t)) return;

  // Decision Logic
  bool fanActive = (t > TEMP_TRIGGER || gas > GAS_TRIGGER);

  if (fanActive) digitalWrite(RELAY_PIN, LOW); 
  else digitalWrite(RELAY_PIN, HIGH);

  // LCD Update
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print((int)t); lcd.print("C G:"); lcd.print(gas);
  
  lcd.setCursor(0, 1);
  if (fanActive) lcd.print("FAN:ON  ");
  else lcd.print("DEC OPT "); // Optimized Decomposition

  lcd.setCursor(9, 1);
  lcd.print("M:"); lcd.print(map(soil, 1023, 0, 0, 100)); lcd.print("%");

  delay(2000); // Prevents relay chatter
}

