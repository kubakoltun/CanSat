#include <SoftwareSerial.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Wyszukiwanie portów TX/RX...");

  for (int i = 0; i < 19; i++) {  // Sprawdź porty od 0 do 18 (możesz dostosować zakres w razie potrzeby)
    Serial.print("Sprawdzanie portu ");
    Serial.print(i);
    Serial.print(": ");

    SoftwareSerial mySerial(i, i);  // Utwórz obiekt SoftwareSerial dla danego portu
    mySerial.begin(9600);  // Rozpocznij komunikację z danym portem

    mySerial.println("Test");  // Wysłanie testowej wiadomości

    delay(100);  // Poczekaj na odpowiedź

    if (mySerial.available() > 0) {
      Serial.println("Znaleziono port!");
    } else {
      Serial.println("Brak odpowiedzi.");
    }

    mySerial.end();  // Zakończ komunikację z danym portem
  }
}

void loop() {
}
