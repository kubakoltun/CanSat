void setup() {
  pinMode(10, INPUT);
  pinMode(12, OUTPUT);
  // Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(10);

  if (buttonState != 0) {
    digitalWrite(12, !digitalRead(12));
    // digitalWrite(12, HIGH);
    // Serial.println("pushed");
    delay(200);
  } 
  // else {
  //   digitalWrite(12, LOW);
  // }

}
