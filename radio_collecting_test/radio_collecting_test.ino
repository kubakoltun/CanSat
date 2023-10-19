#include <M5Stack.h>
#include <LoRaWan-ASR6501.h>

LoRaWan_ASR6501 lora;
Serial_ loraSerial(SERIAL_PORT_HARDWARE);

void setup() {
  M5.begin();
  Serial.begin(115200);
  while (!Serial);

  loraSerial.begin(9600);  // Inicjalizacja komunikacji UART

  if (lora.init()) {
    Serial.println("LoRa module initialized successfully.");
  } else {
    Serial.println("LoRa module initialization failed. Check your connections.");
    while (1);
  }

  if (lora.joinOTAA()) {
    Serial.println("Joined LoRaWAN network.");
  } else {
    Serial.println("Joining LoRaWAN network failed.");
    while (1);
  }
}

void loop() {
  String data = "Komunikat radiowy z urządzenia HP!";
  lora.send(data);

  // Odbieranie danych przez UART
  if (loraSerial.available()) {
    String response = loraSerial.readString();
    Serial.println("Received via UART: " + response);
  }

  delay(5000);  // Adjust the delay as needed
}