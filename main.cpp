/*
 * Arduino Distance Measuring Tool
 * uses ultrasonic sensor to display distance to 2x16 i2c lcd display
 * lcd connections:
 * -GND to GND
 * -VCC to 5v
 * -SDA to analog in 4
 * -SCL to analog in 5
 * 
 * ultrasonic sensor connections
 * -GND to GND
 * -Echo to digital pin
 */
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
/*
 * -Trig to digital pin
 */
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor

 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
//  Serial.begin(9600); // Starting Serial Terminal
  lcd.begin();
  lcd.backlight();
}

void loop() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);

   long feet = inches / 12;
   inches = inches % 12;
   lcd.clear();
   lcd.print(feet);
   lcd.print(" ft");
   lcd.setCursor(0, 1);
   lcd.print(inches);
   lcd.print(" in");
//   Serial.print(inches);
//   Serial.print("in, ");
//   Serial.print(cm);
//   Serial.print("cm");
//   Serial.println();
   delay(100);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

