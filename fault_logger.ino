
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// Use 0x27 or 0x3F based on your LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Try 0x3F if 0x27 doesn't work

const char* faultNames[] = {
  "NONE",         // 0
  "SENSOR_FAIL",  // 1
  "OVERHEAT",     // 2
  "VOLT_DROP",    // 3
  "MEM_ERROR"     // 4
};

uint16_t eepromAddress = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(8, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Logging Faults");

  delay(1000);

  for (int i = 0; i < 5; i++) {
    delay(1000);
    uint8_t faultCode = random(1, 5);
    logFault(faultCode);
    displayFault(faultCode);
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reading EEPROM");
  Serial.println("EEPROM History:");
  readFaults();
}

void loop() {}

void logFault(uint8_t faultCode) {
  uint32_t timestamp = millis();
  EEPROM.write(eepromAddress++, faultCode);
  for (int i = 0; i < 4; i++) {
    EEPROM.write(eepromAddress++, (timestamp >> (8 * i)) & 0xFF);
  }

  digitalWrite(8, HIGH);
  delay(200);
  digitalWrite(8, LOW);

  Serial.print("Logged: ");
  Serial.print(faultNames[faultCode]);
  Serial.print(" at ");
  Serial.print(timestamp);
  Serial.println(" ms");
}

void displayFault(uint8_t faultCode) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FAULT: ");
  lcd.print(faultCode);
  lcd.setCursor(0, 1);
  lcd.print(faultNames[faultCode]);
}

void readFaults() {
  uint16_t addr = 0;
  for (int i = 0; i < 5; i++) {
    uint8_t code = EEPROM.read(addr++);
    uint32_t time = 0;
    for (int j = 0; j < 4; j++) {
      time |= ((uint32_t)EEPROM.read(addr++)) << (j * 8);
    }
    Serial.print("Fault ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(faultNames[code]);
    Serial.print(", Time: ");
    Serial.println(time);
  }
}
