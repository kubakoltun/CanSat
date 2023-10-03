#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>
#include <Seeed_LoRaWAN.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Inicjalizacja obiektu BMP280
Adafruit_BMP280 bmp;

// Inicjalizacja obiektu OneWire
OneWire oneWire(2);

// Inicjalizacja obiektu DallasTemperature
DallasTemperature sensors(&oneWire);

#define LORA_RX 2
#define LORA_TX 3
#define LORA_BAUD 9600

char appEui[] = "YourAppEui"; 
char appKey[] = "YourAppKey"; 

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Grove - LoRa Radio 868MHz Example");

  // Inicjalizacja komunikacji szeregowej z modułem LoRa
  SoftwareSerial loraSerial(LORA_RX, LORA_TX);
  loraSerial.begin(LORA_BAUD);

  // Inicjalizacja modułu LoRa
  while (!LoRaBee.init(loraSerial)) {
    Serial.println("Inicjalizacja modułu LoRa nie powiodła się!");
    delay(10000);
  }
  
  // Konfiguracja kluczy AppEUI i AppKey
  LoRaBee.setAppEUI(appEui);
  LoRaBee.setAppKey(appKey);

  // Sprawdzenie połączenia z siecią LoRa
  while (!LoRaBee.joinABP()) {
    Serial.println("Nie udało się dołączyć do sieci LoRa!");
    delay(10000);
  }

  Serial.println("Połączono z siecią LoRa!");

  // Rozpoczęcie komunikacji z czujnikiem DS18B20
  sensors.begin(); 

  if (!bmp.begin(0x76)) {
    Serial.println(F("Nie znaleziono czujnika BMP280. Sprawdź podłączenie."));
    while (1);
  }
}

void loop() {
  // Odczyt temperatury z czujnika BMP280
  float temperatureBMP = bmp.readTemperature();
  float pressureBMP = bmp.readPressure() / 100.0F; // Zamiana na hPa

  Serial.print(F("Temperatura BMP280: "));
  Serial.print(temperatureBMP);
  Serial.println(" °C");

  Serial.print(F("Ciśnienie BMP280: "));
  Serial.print(pressureBMP);
  Serial.println(" hPa");

  // Odczyt temperatury z czujnika DS18B20
  sensors.requestTemperatures();
  float temperatureDS18B20 = sensors.getTempCByIndex(0);

  // Sprawdzenie, czy odczytano poprawną temperaturę
  if (temperatureDS18B20 != DEVICE_DISCONNECTED_C) {
    // Wyświetlenie temperatury na monitorze szeregowym
    Serial.print("Temperatura DS18B20: ");
    Serial.print(temperatureDS18B20);
    Serial.println(" °C");
  } else {
    // Jeśli nie udało się odczytać temperatury, wyświetl komunikat o błędzie
    Serial.println("Błąd odczytu temperatury z DS18B20.");
  }

  // Przykład wysyłania wiadomości przez LoRa
  String message = "Pierwszy komunikat radiowy!";
  // Wysłanie wiadomości z priorytetem 1
  LoRaBee.send(1, message); 

  // Oczekiwanie na potwierdzenie
  int waitCount = 0;
  while (!LoRaBee.waitSend()) {
    waitCount++;
    if (waitCount > 30) {
      Serial.println("Przekroczono limit czasu czekania na potwierdzenie.");
      break;
    }
    delay(1000);
  }

  delay(5000); 
}
