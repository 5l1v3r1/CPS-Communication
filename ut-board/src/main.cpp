#include <Arduino.h>
#include <Wire.h>

#define SENSOR_ADDRESS 110
#define ON_OFF_REG 0

#define DATA_X_BASE 10
#define DATA_Y_BASE 40

float final_reasult = 0;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(100);

    // Init UT Sensor
    Wire.beginTransmission(SENSOR_ADDRESS);
    Wire.write(ON_OFF_REG);
    Wire.write(1);
    Wire.endTransmission();
}

byte get_data_from_address(int address, byte reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(SENSOR_ADDRESS, 1);
    return Wire.read();
}

float get_float_from_address(int address, byte baseAddress) {
    float result;
    byte* result_b = (byte *)&result;

    result_b[0] = get_data_from_address(address, baseAddress + 0);
    result_b[1] = get_data_from_address(address, baseAddress + 1);
    result_b[2] = get_data_from_address(address, baseAddress + 2);
    result_b[3] = get_data_from_address(address, baseAddress + 3);

    return result;
}

void loop() {
    float x = get_float_from_address(SENSOR_ADDRESS, DATA_X_BASE);
    float y = get_float_from_address(SENSOR_ADDRESS, DATA_Y_BASE);
    final_reasult += x * x + y * y;
	Serial.println(final_reasult);
    delay(100);
}