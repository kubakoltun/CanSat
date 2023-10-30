#include <SoftwareSerial.h>

#define PWM_PIN  3

SoftwareSerial mySerial(0, PWM_PIN);  

void setup() {
  pinMode(PWM_PIN, OUTPUT);
  // Inicjalizacja komunikacji szeregowej
  Serial.begin(115200);  
  mySerial.begin(115200); 

  analogWrite(PWM_PIN, 409);
}

void loop() {
   if (mySerial.available() >= 1) {
    // Odczytaj 1 bajt danych (8 bitów) z czujnika
    byte data = mySerial.read();
    Serial.print("Odczytano dane bit: ");
    Serial.println(data);



    // Wartości bitowe z D7 do D0
    byte data_bits = data & 0xFF;

    // Serial.print("Odczytano dane (BIN): ");
    // Serial.println(data_bits, BIN);

    // Serial.print("Odczytano dane (DEC): ");
    // Serial.println(data_bits, DEC);
  }
}
