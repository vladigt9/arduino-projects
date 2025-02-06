# Temperature/Humidity Display with 7-Segment (12 pins) DHT11 Sensor

This project reads temperature data from a DHT11 sensor and displays the temperature on a 4-digit 7-segment display. The display shows the temperature in Celsius with two digits representing the temperature and one digit displaying the Celsius symbol ('C') or the humidity with 3 digits for the persentage and a symbol 'H' at the end (for humidity).

## Project Overview

This project achieves the following:

- Reads temperature from a DHT11 sensor.
- Displays the temperature on a 4-digit 7-segment display.
- Updates the temperature and humidity display every second (or faster).

## Dependencies

- **SimpleDHT Library**: Used for communication with the DHT11 temperature and humidity sensor.
  - You can install it via Arduino Library Manager or manually from GitHub: https://github.com/winlinvip/SimpleDHT

## Hardware Requirements

- **DHT11 Temperature and Humidity Sensor**: Connected to pin 13.
- **4-Digit 7-Segment Display**: Connected to pins 1 to 12 (configured in the code).
  
## Pin Configuration

- **Segment Pins** (A, B, C, D, E, F, G, DP): Connected to pins 8, 6, 3, 4, 5, 7, 2, 1 respectively.
- **Digit Pins** (1, 2, 3, 4): Connected to pins 9, 10, 11, 12 respectively.
- **DHT11 Sensor Pin**: Connected to pin 13.

## Code Explanation

### 1. **Pin Initialization**
In the `setup()` function, the segment and digit pins are configured as outputs, and the initial state is set to LOW for segments and HIGH for digits to turn off the display.

### 2. **Reading Temperature and Humidity**
The `loop()` function reads the temperature and the humidity from the DHT11 sensor. If the sensor fails to read, an error message is printed to the Serial Monitor.

### 3. **Displaying Temperature**
The `displayTemperature()` function extracts the tens and ones places of the temperature and displays the digits on the 7-segment display. It uses a `digitMap` array to map numbers (0-9) and the Celsius symbol to the correct segments on the display.

### 4. **Displaying Humidity**
The `displayHumidity()` function extracts the hundreds, the tens and the ones places of the humidity and displays the digits on the 7-segment display. It uses a `digitMap` array to map numbers (0-9) and the H symbol to the correct segments on the display.


### 5. **Segment Control**
The `setSegments()` function controls the 8 segment pins to light up the appropriate segments for each digit being displayed.

### 6. **Display Update Interval**
The display updates around every second, and each digit stays on the screen for a brief period to create a visual persistence effect.

## Usage

1. Connect the DHT11 sensor and 7-segment display to your Arduino as described in the pin configuration.
2. Install the SimpleDHT library.
3. Upload the sketch to your Arduino board.
4. The temperature in Celsius will be displayed on the 7-segment display.
5. The humidity in percentages will be displayed on the 7-segment display.

## Notes

- The current version of the project supports temperature ranges up to 99°C.
- You can adjust the display update interval by modifying the `delay(1000)` in the `loop()` function.

---
