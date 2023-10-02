#include <OneWire.h>
#include <DallasTemperature.h>

// Inicjalizacja obiektu OneWire
OneWire oneWire(2);

// Inicjalizacja obiektu DallasTemperature
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();  // Rozpoczęcie komunikacji z czujnikiem DS18B20
}

void loop() {
  sensors.requestTemperatures(); // Wysłanie żądania pomiaru temperatury

  // Odczyt temperatury z czujnika DS18B20
  float temperatureCelsius = sensors.getTempCByIndex(0);

  // Sprawdzenie, czy odczytano poprawną temperaturę
  if (temperatureCelsius != DEVICE_DISCONNECTED_C) {
    // Wyświetlenie temperatury na monitorze szeregowym
    Serial.print("Temperatura: ");
    Serial.print(temperatureCelsius);
    Serial.println(" °C");
  } else {
    // Jeśli nie udało się odczytać temperatury, wyświetl komunikat o błędzie
    Serial.println("Błąd odczytu temperatury.");
  }

  delay(1000); // Poczekaj 1 sekundę przed kolejnym odczytem
}
