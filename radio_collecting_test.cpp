#include <M5Stack.h>
#include <LoRaWan-ASR6501.h>

LoRaWan_ASR6501 lora;

void setup() {
  M5.begin();
  Serial.begin(115200);

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
  String data = "Hello from M5Stack!";
  lora.send(data);

  // Wait for a response (you can customize this part based on your needs)
  String response = lora.receive();

  if (response != "") {
    Serial.println("Received: " + response);
  }

  delay(5000);  // Adjust the delay as needed
}