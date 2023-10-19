#include <Arduino.h>
#include <LoRaWan-STM32.h> 

LoRaWanClass lora;  

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (lora.begin(EU868)) { ć
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
  String data = "Komunikat radiowy z urządzenia Arduino !";
  lora.sendData(data, strlen(data), false);

  lora.waitUntil(TX_COMPLETE); 

  if (lora.packetReceived()) {
    String response = lora.readData();
    Serial.println("Received: " + response);
  }

  delay(5000);  
}