#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // Inicjalizacja obiektu BMP280

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println(F("Nie znaleziono czujnika BMP280. Sprawdź podłączenie."));
    while (1);
  }
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // Zamiana na hPa

  Serial.print(F("Temperatura: "));
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print(F("Ciśnienie: "));
  Serial.print(pressure);
  Serial.println(" hPa");

  delay(1000); // Odczyt co 1 sekundę
}
