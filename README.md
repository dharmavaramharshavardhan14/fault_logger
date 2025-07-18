
# Arduino Fault Logger Project

## Description
This Arduino project logs random fault codes to the EEPROM along with a timestamp and displays them on an I2C LCD. It also prints the fault log to the Serial Monitor.

## Components Used
- Arduino Uno
- I2C LCD 16x2
- LED (status indicator)
- 220 ohm resistor
- EEPROM (internal to Arduino Uno)

## How It Works
- 5 random fault codes are generated and logged.
- Each fault is stored in EEPROM with a timestamp.
- The LCD displays each fault and the corresponding message.
- LED blinks each time a fault is logged.
- At the end, EEPROM content is read and printed to the Serial Monitor.

## Wiring Instructions
- LCD SDA -> A4 (Arduino)
- LCD SCL -> A5 (Arduino)
- LCD VCC -> 5V
- LCD GND -> GND
- LED Anode -> Digital Pin 8 (via 220Ω resistor)
- LED Cathode -> GND

## Output
See the output image for the LCD display with fault message.

## Files
- `fault_logger.ino` - Arduino sketch
- `output.png` - Screenshot of the output
- `README.md` - Project overview and instructions
