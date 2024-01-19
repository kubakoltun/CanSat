#include <RH_RF95.h>
#include <SoftwareSerial.h>

#define COMSerial Serial
#define ShowSerial SerialUSB

RH_RF95<HardwareSerial> rf95(COMSerial);

int led = 13;


void setup() {
    ShowSerial.begin(115200);
    ShowSerial.println("RF95 server test.");

    pinMode(led, OUTPUT);

    if (!rf95.init()) {
        ShowSerial.println("init failed");
        while (1);
    }

    rf95.setFrequency(868.0);
}

void loop() {
    if (rf95.available()) {
        // Should be a message for us now
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);
        if (rf95.recv(buf, &len)) {
            digitalWrite(led, HIGH);

            ShowSerial.print("got request: ");
            ShowSerial.println((char*)buf);

            // Send a reply
            uint8_t data[] = "And hello back to you";
            rf95.send(data, sizeof(data));
            rf95.waitPacketSent();
            ShowSerial.println("Sent a reply");

            digitalWrite(led, LOW);
        } else {
            ShowSerial.println("recv failed");
        }
    } else {
      digitalWrite(led, HIGH);
      delay(2000);
      digitalWrite(led, LOW);
      delay(2000);
    }
}


