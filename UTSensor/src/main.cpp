#include <Arduino.h>
#include <Wire.h>

#define SENSOR_ADDRESS 110
#define ON_OFF_REG 0

#define DATA_X_BASE 10
#define DATA_Y_BASE 40

bool isOn = false;
float x_data, y_data;
byte x[4];
byte y[4];

byte buff;

byte t = 4;

void receiveEvent(int howMany) {
	byte data[2];
	for(int i = 0; i < howMany; i++)
		data[i] = Wire.read();

	if(howMany == 2 && data[0] == ON_OFF_REG) {
		isOn = data[1] == 1;
		return;
	}

	if(howMany == 2) // BAD REQUEST
		buff = 128;
	else if(data[0] == ON_OFF_REG) // REQUEST ON_OFF
		buff = isOn ? 1 : 0;
	else if(!isOn) // IF IS OFF DO NOTING
		buff = buff;
	else if(data[0] >= DATA_X_BASE && data[0] < DATA_X_BASE + 4) // X REQESTED
		buff = x[data[0] - DATA_X_BASE];
	else if(data[0] >= DATA_Y_BASE && data[0] < DATA_Y_BASE + 4) // Y REQESTED
		buff = y[data[0] - DATA_Y_BASE];
	else // OTHER REQ REQESTED
		buff = 128;
}

void requestEvent() {
	Wire.write(buff);
}

void setup() {
	Serial.begin(2300);
	Wire.begin(SENSOR_ADDRESS);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
	delay(100);
}

void loop() {
	Serial.print("# Status: "); Serial.print(isOn ? "ON" : "OFF");
	Serial.print(" Data: "); Serial.print(x_data); Serial.print(" "); Serial.print(y_data);
	Serial.print(" BUFF: "); Serial.println(buff);
	if(isOn) {
		x_data = sin(t);
		y_data = cos(t);

		byte *x_ref = (byte *)&x_data;
		byte *y_ref = (byte *)&y_data;
		
		x[0] = x_ref[0];
		x[1] = x_ref[1];
		x[2] = x_ref[2];
		x[3] = x_ref[3];

		y[0] = y_ref[0];
		y[1] = y_ref[1];
		y[2] = y_ref[2];
		y[3] = y_ref[3];

		t++;
	}

	delay(100);
}
