#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
String humidity = "...";
String outTemp = "...";
String weatherDescription = "...";

void setup() {
	Serial.begin(9600);
	lcd.init();                      // initialize the lcd 
	lcd.init();
	// Print a message to the LCD.
	lcd.backlight();
	sensors.begin();
}

void loop() {

	displayWeatherDiscription(0, 0);

	displayOutsideTemperature(0, 1);

	displayInsideTemperature(0, 2);

	displayHumidity(0, 3);
}

void displayHumidity(int x, int y) {
	lcd.setCursor(x, y);
	lcd.print("Hum: ");
	lcd.print(humidity);
	lcd.print("% ");
}

void displayInsideTemperature(int x, int y) {
	lcd.setCursor(x, y);
	lcd.print("Temp: ");
	lcd.print(getTemperature());
	lcd.print("C ");
}

void displayOutsideTemperature(int x, int y) {
	lcd.setCursor(x, y);
	lcd.print("OutTemp: ");
	lcd.print(outTemp);	
	lcd.print("C ");
}

void displayWeatherDiscription(int x, int y) {
	lcd.setCursor(x, y);
	lcd.print("Weather: ");
	lcd.print(weatherDescription);
}



float getTemperature() {
	sensors.requestTemperatures();

	return sensors.getTempCByIndex(0);
}

void serialEvent() {
	String incomingString = Serial.readStringUntil('\n');
	int firstCommaIndex = incomingString.indexOf(';');
	int secondCommaIndex = incomingString.indexOf(';', firstCommaIndex + 1);
	humidity = incomingString.substring(0, firstCommaIndex);
	outTemp = incomingString.substring(firstCommaIndex + 1, secondCommaIndex);
	weatherDescription = incomingString.substring(secondCommaIndex + 1);
	lcd.clear();
}

