#include <RH_RF95.h>

#define COMSerial Serial1
#define ShowSerial Serial

RH_RF95<HardwareSerial> rf95(COMSerial);

void setup() {
    ShowSerial.begin(9600);
    // COMSerial.begin(115200);
    ShowSerial.println("RF95 client test.");

    if (!rf95.init()) {
        ShowSerial.println("init failed");
        while (1);
    }

    rf95.setFrequency(868.0);
}

void loop() {
    ShowSerial.println("Sending to rf95_server");
    uint8_t data[] = "Here are my data: data - signed Client";
    rf95.send(data, sizeof(data));
    rf95.waitPacketSent();

    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.waitAvailableTimeout(3000)) {
        if (rf95.recv(buf, &len)) {
            ShowSerial.print("got reply: ");
            ShowSerial.println((char*)buf);
        } else {
            ShowSerial.println("recv failed");
        }
    } else {
        ShowSerial.println("No reply, is rf95_server running?");
    }

    delay(3000);
}
