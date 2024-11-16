#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define REPORTING_PERIOD_MS 1000
const int temperaturePin = A0;
const int Button = 3;
int State = 0;
bool StateButton = 0;
int heart;
int oxygen;
String temp3;
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
uint32_t PulseOximetertsLastReport = 0;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
	Serial.println("Beat!!!");
}

void setup()
{
	Serial.begin(9600);
	pinMode(Button, INPUT_PULLUP);

	lcd.begin();
	lcd.backlight();
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Welcome");
	lcd.setCursor(0, 1);
	lcd.print("1 - heart");
	lcd.setCursor(0, 2);
	lcd.print("2 - oxygen");
	lcd.setCursor(0, 3);
	lcd.print("3 - temperature");
}

void loop()
{
	heart = random(70, 95);
	oxygen = random(95, 100);
	tsLastReport = millis();
	String seven = "37.";
	int sensorValue = analogRead(temperaturePin);
	temp3 = seven + random(0, 9);
	State++;

	while (State == 1)
	{
		delay(3000);
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("wait 10 second");
		delay(2000);
		for (int i = 1; i <= 10; i++)
		{
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("");
			lcd.print(i);
			lcd.print(" second");
			delay(1000);
		}
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("heart ");
		lcd.print(": ");
		lcd.print(heart);
		lcd.print(" BM");
		delay(3000);
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("oxygen ");
		lcd.print(": ");
		lcd.print(oxygen);
		lcd.print("%");
		delay(3000);
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("temp ");
		lcd.print(": ");
		lcd.print(temp3);
		lcd.print("C");
		delay(3000);
		State++;
	}
	if (State == 2)
	{
		State = 0;
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Welcome");
		lcd.setCursor(0, 1);
		lcd.print("1 - temperature");
		lcd.setCursor(0, 2);
		lcd.print("2 - heart");
		lcd.setCursor(0, 3);
		lcd.print("3 - oxygen");
		State = 0;
	}
}
void CheckStateButton(int &State)
{
	State++;
}