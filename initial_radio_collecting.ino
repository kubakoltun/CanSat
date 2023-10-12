#include <SPI.h>
#include <LoRaWan-Arduino.h>

#define SENDER
// 868MHz
#define BAND 868E6  

void setup() {
  Serial.begin(115200);
  while (!Serial);

  LoRaWAN.begin(BAND);

  #ifdef SENDER
    // Wysyłanie danych
    LoRaWAN.send("Hello, World!", 13);
  #else
    // Odbieranie danych
    LoRaWAN.onReceive([](const uint8_t *data, size_t size) {
      Serial.print("Odebrano: ");
      Serial.write(data, size);
      Serial.println();
    });
    LoRaWAN.receive();
  #endif
}

void loop() {
  #ifdef SENDER
    // Wysyłanie danych co 10 sekund
    LoRaWAN.loop();
    delay(10000);
  #else
    // Odbieranie danych
    LoRaWAN.loop();
  #endif
}
