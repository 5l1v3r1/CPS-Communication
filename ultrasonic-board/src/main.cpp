#include <Arduino.h>
#include <Ultrasonic.h>
#include <LM35.h>

#define ULTRA_TRIG 7
#define ULTRA_ECHO 6

Ultrasonic ultrasonic(ULTRA_TRIG, ULTRA_ECHO);
LM35 temp(A0);

void setup() {
  Serial.begin(9600);
  ultrasonic.setTimeout(40000UL);
}

void loop() {
  Serial.print(ultrasonic.read());
  Serial.print("|");
  Serial.println(temp.cel());
  delay(100);
}