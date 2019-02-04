#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Wire.h>
#include <AltSoftSerial.h>

#define LIQ_D4 11
#define LIQ_D5 10
#define LIQ_D6 9
#define LIQ_D7 7
#define LIQ_EN 12
#define LIQ_RST 13

#define SOFWARE_SERIAL_RX 8
#define SOFWARE_SERIAL_TX 6

LiquidCrystal lcd(LIQ_RST, LIQ_EN, LIQ_D4, LIQ_D5, LIQ_D6, LIQ_D7);
AltSoftSerial altSerial;

float ut_sensor = 0;
float distance = 0;
float temp = 0;

void setup() {
    Serial.begin(9600);
    altSerial.begin(9600);
    lcd.begin(20,4);
}

void update_ut_sensor() {
    if(Serial.available()) {
        Serial.readStringUntil('\n');
        ut_sensor = Serial.readStringUntil('\n').toFloat();
    }
}

void update_distance() {
    if(altSerial.available()) {
        altSerial.readStringUntil('\n');
        distance = altSerial.readStringUntil('|').toFloat();
        temp = altSerial.readStringUntil('\n').toFloat();
    }
}

void loop() {

    lcd.home();
    lcd.print("UT Sensor: ");
    lcd.print(ut_sensor);

    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance);

    lcd.setCursor(0, 2);
    lcd.print("Temp: ");
    lcd.print(temp);

    update_ut_sensor();
    update_distance();
}