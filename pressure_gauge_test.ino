#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Inicjalizacja obiektu BMP280
Adafruit_BMP280 bmp; 

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println(F("Nie znaleziono czujnika BMP280. Sprawdź podłączenie."));
    while (1);
  }
}

void loop() {
  float temperature = bmp.readTemperature();
  // Zamiana na hPa
  float pressure = bmp.readPressure() / 100.0F; 

  Serial.print(F("Temperatura: "));
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print(F("Ciśnienie: "));
  Serial.print(pressure);
  Serial.println(" hPa");

  delay(1000);
}
