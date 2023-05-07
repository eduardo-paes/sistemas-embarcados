#include <Ultrasonic.h>

const int I1 = 11, 
          I2 = 10, 
          I3 = 6, 
          I4 = 5;

Ultrasonic ultrassom(2, 3);
long distance;

void setup() {
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);
}

void runWheel(int port, int max) {
  for (int i = 70; i < 256; i++) {
    analogWrite(port, i);
    delay(20);
  }
  delay(1000);
}

void stop() {
  analogWrite(I1, 0);
  analogWrite(I2, 0);
  analogWrite(I3, 0);
  analogWrite(I4, 0);
}

void breakStop() {
  analogWrite(I1, 255);
  analogWrite(I2, 255);
  analogWrite(I3, 255);
  analogWrite(I4, 255);
}

void goBack() {
  analogWrite(I2, 255);
  analogWrite(I4, 255);
  delay(1000);
}

void rotateLeft() {
  analogWrite(I2, 255);
  analogWrite(I3, 255);
  delay(1000);
}

void loop() {
  distance = ultrassom.Ranging(CM);
  if (distance < 10) {
    stop();
    delay(500);
    goBack();
    stop();
    delay(500);
    rotateLeft();
    stop();
    delay(500);
  }
  else {
    analogWrite(I1, 255);
    analogWrite(I3, 255);
  }
}
 