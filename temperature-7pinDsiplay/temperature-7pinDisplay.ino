#include <SimpleDHT.h>

// Define segment pins (A, B, C, D, E, F, G, DP)
const int segmentPins[8] {8, 6, 3, 4, 5, 7, 2, 1}; 

// Define digit select pins (1, 2, 3, 4) they are in reverse on the display [4,3,2,1]
const int digitPins[4] {9, 10, 11, 12};

// DHT11 Temperature Sensor
const int pinDHT11 {13}; 
SimpleDHT11 dht11;

// Digit representation for 0-9 and C for celcius and H for humidity
const byte digitMap[12] {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b00111001, // C
  0b01110110, // H
};

// Variable to store the digit representation of C for Celsius
const byte C {0b00111001};

void setup() {
    Serial.begin(9600);

    // Set segment pins as OUTPUT
    for (int i = 0; i < 8; i++) {
        pinMode(segmentPins[i], OUTPUT);
        digitalWrite(segmentPins[i], LOW);  // Turn off segments
    }

    // Set digit pins as OUTPUT
    for (int i = 0; i < 4; i++) {
        pinMode(digitPins[i], OUTPUT);
        digitalWrite(digitPins[i], HIGH);  // Turn off digits
    }
}

void loop() {
    byte temperature = 0;
    byte humidity = 0;
    byte data[40] = {0};

    if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
        Serial.println("Read fail");
        return;
    }

    // Used for debugging
    // Serial.print("\nTemperature: ");
    // Serial.print((int)temperature);
    // Serial.print((int)humidity);
    // Serial.println(" *C");

    // Display temperature on 7-segment
    displayTemperature(temperature);

    delay(100);

    displayHumidity(humidity);
    delay(100); // Update every second
}

// Function to display a number (00-99) on the 7-segment display
void displayTemperature(int number) {
    int digits[4] = {0, 0, 0, 0}; // Array to hold individual digits

    // Extract individual digits (supports temperatures up to 99°C)
    digits[3] = (number / 10) % 10; // Tens place
    digits[2] = number % 10;        // Ones place
    digits[1] = 0; // Unused digit
    digits[0] = 10; // Digit used for Celsius

    unsigned long startTime = millis();
    while (millis() - startTime < 2000) {  // Keep displaying for 1 second
        for (int d = 0; d < 4; d++) {
          if (d == 1)
          {
            // skip loop for faster iteration when on an unused digit
            continue;
          }
          
          digitalWrite(digitPins[d], LOW); // Turn on digit (LOW for common cathode)

          setSegments(digitMap[digits[d]]); // Set the correct number

          delay(5); // Short delay for persistence (adjust if needed)

          digitalWrite(digitPins[d], HIGH); // Turn off digit before next one
        }
    }
}

void displayHumidity(int number)
{
  int digits[4] = {0, 0, 0, 0}; // Array to hold individual digits

    // Extract individual digits (supports humidity up to 100)
    digits[3] = (number / 100) % 10;  // Hundreds place (will be 0 if number is < 100)
    digits[2] = (number / 10) % 10;   // Tens place
    digits[1] = number % 10;          // Ones place
    digits[0] = 11; // Digit used for Celsius

    unsigned long startTime = millis();
    while (millis() - startTime < 2000) {  // Keep displaying for 1 second
        for (int d = 0; d < 4; d++) {
          
          digitalWrite(digitPins[d], LOW); // Turn on digit (LOW for common cathode)

          setSegments(digitMap[digits[d]]); // Set the correct number

          delay(5); // Short delay for persistence (adjust if needed)

          digitalWrite(digitPins[d], HIGH); // Turn off digit before next one
        }
    }
}


// Function to set the segment pins according to the digit map
void setSegments(byte segments) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(segmentPins[i], (segments >> i) & 1);
    }
}
