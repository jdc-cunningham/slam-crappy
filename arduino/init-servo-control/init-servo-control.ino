
// The I2C part of this code is based on this tutorial:
// https://dronebotworkshop.com/i2c-arduino-raspberry-pi/
// laughably struggled with simple string split
// https://forum.arduino.cc/index.php?topic=155667.0

#include <Wire.h>
#include <Servo.h>

Servo tiltServo;
Servo panServo;

int panServoPos = 105;
int tiltServoPos = 92;

String moveServo = ""; // p or t for pan/tilt
String moveServoPos = ""; // 0-180 casted to int

void setup() {
  Serial.begin(9600);
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent);
  panServo.attach(2);
  tiltServo.attach(3);
  panServo.write(panServoPos);
  tiltServo.write(tiltServoPos);
}

void receiveEvent(int bytes) {
  String fullCommand = "";
  int loopCounter = 0;
  moveServo = "";
  moveServoPos = "";
  
  while (Wire.available()) {
    char c = Wire.read();

    if (loopCounter == 1) {
      moveServo = c;
    }

    if (loopCounter > 1 and loopCounter < 5) {
      moveServoPos += c;
    }

    loopCounter++;
  }

  if (moveServo == "p") {
    panServo.write(moveServoPos.toInt());
  }
  
  if (moveServo == "t") {
    tiltServo.write(moveServoPos.toInt());
  }
}

void loop() {
  delay(100);
}