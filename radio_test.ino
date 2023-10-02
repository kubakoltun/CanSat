#include <SoftwareSerial.h>
#include <Seeed_LoRaWAN.h>

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
}

void loop() {
  // Przykład wysyłania wiadomości
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
  // Odczekaj przed wysłaniem kolejnej wiadomości
  delay(5000); 
}
