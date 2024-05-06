#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); // Define software serial object for Bluetooth communication
(TX, RX respectively)
String receivedCommand; // String to store incoming message from Bluetooth
// Define motor pins
int RMF = 3; // Right motor forward
int RMB = 4; // Right motor backward
int LMF = 5; // Left motor forward
int LMB = 6; // Left motor backward
// Define command execution variables
unsigned long commandStartTime = 0; // Variable to store the start time of the command
const unsigned long commandDuration = 2000; // Duration for which each command
should execute (in milliseconds)
void setup() {
BT.begin(9600); // Initialize Bluetooth serial communication
Serial.begin(9600); // Initialize serial communication for debugging
// Set motor pins as outputs
pinMode(RMF, OUTPUT);
pinMode(RMB, OUTPUT);
pinMode(LMF, OUTPUT);
pinMode(LMB, OUTPUT);
}
void loop() {
// Check for available data from Bluetooth
while (BT.available()) { // Check if there is an available byte to read
delay(10); // Delay added to ensure stability
char c = BT.read(); // Read a character from Bluetooth
receivedCommand += c; // Build the command string
}
// Process received commands
if (receivedCommand.length() > 0) {
// Record the start time of the command
commandStartTime = millis();
// Execute commands based on received voice commands
if (receivedCommand == "back") {
// Set motor speeds for backward movement
analogWrite(RMF, 80);
analogWrite(LMF, 80);
digitalWrite(RMB, LOW);
24
digitalWrite(LMB, LOW);
}
else if (receivedCommand == "forward") {
// Set motor speeds for forward movement
digitalWrite(RMF, LOW);
digitalWrite(LMF, LOW);
analogWrite(RMB, 130);
analogWrite(LMB, 130);
}
else if (receivedCommand == "right") {
// Set motor speeds for right turn
digitalWrite(RMF, LOW);
digitalWrite(LMF, LOW);
digitalWrite(RMB, LOW);
analogWrite(LMB, 130);
}
else if (receivedCommand == "left") {
// Set motor speeds for left turn
digitalWrite(RMF, LOW);
digitalWrite(LMF, LOW);
analogWrite(RMB, 130);
digitalWrite(LMB, LOW);
}
// Continue executing the command until the command duration is reached
while (millis() - commandStartTime < commandDuration) {
// Check for new commands
while (BT.available()) {
char c = BT.read();
receivedCommand += c;
}
}
// Stop the motors after the command duration
digitalWrite(RMF, LOW);
digitalWrite(LMF, LOW);
digitalWrite(RMB, LOW);
digitalWrite(LMB, LOW);
// Reset the command variable
receivedCommand = "";
}
}
