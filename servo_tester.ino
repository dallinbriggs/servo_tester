#include <Servo.h>

Servo myservo;

int potpin = 2;
int potval = 0;
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(potpin);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  potval = total / numReadings;
  potval = map (potval, 0, 1023, 500, 2500);
  myservo.writeMicroseconds(potval);
  Serial.println(potval);
  delay(15);
}
