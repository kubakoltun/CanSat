int ledPin = 13;

void setup() {
  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(2000);                      
  // digitalWrite(LED_BUILTIN, LOW);  
  // delay(2000);       
  digitalWrite(12, HIGH);
  delay(2000);                      
  digitalWrite(12, LOW);  
  delay(2000);                 
}
