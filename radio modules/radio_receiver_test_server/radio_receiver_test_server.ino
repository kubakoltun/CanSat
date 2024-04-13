#include <RH_RF95.h>
#include <SoftwareSerial.h>

SoftwareSerial SSerial(10, 11); // RX, TX
#define COMSerial SSerial
#define ShowSerial Serial
RH_RF95<SoftwareSerial> rf95(COMSerial);

int led = 13;

void setup() {
    ShowSerial.begin(115200);
    // COMSerial.begin(115200);
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
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);
        if (rf95.recv(buf, &len)) {
            digitalWrite(led, HIGH);

            ShowSerial.print("got request: ");
            ShowSerial.println((char*)buf);

            uint8_t data[] = "And hello back to you";
            rf95.send(data, sizeof(data));
            rf95.waitPacketSent();
            ShowSerial.println("Sent a reply");

            digitalWrite(led, LOW);
        } else {
            ShowSerial.println("recv failed");
        }
    }
}
