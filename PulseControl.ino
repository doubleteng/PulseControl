#include <Wire.h>

// Variables for timing, data, and motor control
unsigned long motor1StepDelay, motor2StepDelay, motor3StepDelay;  // Delay between steps for each motor
String serialDataBuffer = "";  // Buffer for incoming serial data
int commaCount, maxDistance = 600, range; // maxDistance is the maximum allowable range
int parsedData[6] = {0, 0, 0, 0, 0, 0};  // Array to store parsed serial input data for three motors

// Define pins for each motor
const int motor1DirPin = 2, motor1StepPin = 3;
const int motor2DirPin = 4, motor2StepPin = 5;
const int motor3DirPin = 6, motor3StepPin = 7;
const int sensorPin = 8;  // Input pin, possibly for range sensor or limit switch

void setup() {
    Serial.begin(9600);  // Start serial communication at 9600 baud
    Wire.begin();  // Initialize I2C communication

    // Set pin modes for direction and step control for each motor
    pinMode(motor1DirPin, OUTPUT);
    pinMode(motor1StepPin, OUTPUT);
    pinMode(motor2DirPin, OUTPUT);
    pinMode(motor2StepPin, OUTPUT);
    pinMode(motor3DirPin, OUTPUT);
    pinMode(motor3StepPin, OUTPUT);
    pinMode(sensorPin, INPUT);   // Input pin for sensor
    digitalWrite(sensorPin, HIGH);  // Enable pull-up resistor on sensor pin
}

void loop() {  
    // Read incoming serial data if available
    while (Serial.available() > 0) {
        serialDataBuffer += char(Serial.read());  // Append character to buffer
        delay(2);  // Small delay to ensure data is fully received
    }

    // If buffer has data, parse it
    if (serialDataBuffer.length() > 0) {
        commaCount = 0;
        for (int i = 0; i < serialDataBuffer.length(); i++) {
            if (serialDataBuffer[i] == ',') {  // Check for comma separator
                commaCount++;
            } else {
                parsedData[commaCount] = parsedData[commaCount] * 10 + (serialDataBuffer[i] - '0');
            }
        }

        // Reset buffer for next read
        serialDataBuffer = "";

        // Calculate step delays based on parsed data
        motor1StepDelay = 625 / parsedData[1];  // Speed setting for motor 1
        motor2StepDelay = 625 / parsedData[3];  // Speed setting for motor 2
        motor3StepDelay = 625 / parsedData[5];  // Speed setting for motor 3

        // Set motor directions based on parsed data
        digitalWrite(motor1DirPin, parsedData[0] == 1 ? HIGH : LOW);  // Direction for motor 1
        digitalWrite(motor2DirPin, parsedData[2] == 1 ? HIGH : LOW);  // Direction for motor 2
        digitalWrite(motor3DirPin, parsedData[4] == 1 ? HIGH : LOW);  // Direction for motor 3

        // Reset parsed data for next read
        for (int i = 0; i < 6; i++) parsedData[i] = 0;
    }

    // Step each motor if conditions are met
    if (maxDistance > range && digitalRead(sensorPin) == HIGH) {
        for (int i = 0; i < 60000; i++) {
            // Motor 1 step
            digitalWrite(motor1StepPin, HIGH);
            delayMicroseconds(motor1StepDelay);
            digitalWrite(motor1StepPin, LOW);
            delayMicroseconds(motor1StepDelay);

            // Motor 2 step
            digitalWrite(motor2StepPin, HIGH);
            delayMicroseconds(motor2StepDelay);
            digitalWrite(motor2StepPin, LOW);
            delayMicroseconds(motor2StepDelay);

            // Motor 3 step
            digitalWrite(motor3StepPin, HIGH);
            delayMicroseconds(motor3StepDelay);
            digitalWrite(motor3StepPin, LOW);
            delayMicroseconds(motor3StepDelay);

            // Break out of loop if new serial data is received
            if (Serial.available() > 0) {
                break;
            }
        }
    }
}
