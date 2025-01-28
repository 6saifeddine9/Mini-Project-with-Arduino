#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
const unsigned long MEASURE = 25000UL;
const float SOUND = 340.0 / 1000;
const byte TRIG = 8;
const byte ECHO = 9;
int buzz = 7;
DHT temp(2, DHT11);

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  pinMode(buzz, OUTPUT);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  temp.begin();
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long mesure = pulseIn(ECHO, HIGH, MEASURE);
  float distance = mesure / 2.0 * SOUND;
  lcd.setCursor(0, 0);
  lcd.print(F("Distance:"));
  lcd.print(distance / 10.0);
  lcd.print(F("cm "));
  delay(500);
  if ((distance / 10.0) <= 5 && (distance / 10.0) >= 1) {
    tone(buzz, 1000);
    delay(500);
    noTone(buzz);
  } else if ((distance / 10.0) == 0) {
    tone(buzz, 1000);
  } else {
    noTone(buzz);
  }
  lcd.setCursor(0, 1);
  lcd.print(F("Temperature:"));
  lcd.print(String(temp.readTemperature() - 0.7));
  lcd.print(F("°C"));
}
