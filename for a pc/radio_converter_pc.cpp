#include "D:\notatki\cansat\CanSat\libraries\Grove_-_LoRa_Radio_433MHz_868MHz\RH_RF95.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Symulacja SerialUSB na komunikację szeregowa (może być używane do debugowania)
class SerialUSB {
public:
    void begin(int baudrate) {
        // Inicjalizacja komunikacji szeregowej (możesz dostosować do swoich potrzeb)
    }

    void println(const std::string& message) {
        // Wypisanie komunikatu (możesz dostosować do swoich potrzeb)
        std::cout << message << std::endl;
    }
};

// Klasa symulująca komunikację szeregową za pośrednictwem strumieni
class SerialPort {
public:
    void begin(int baudrate) {
        // Inicjalizacja komunikacji szeregowej (możesz dostosować do swoich potrzeb)
    }

    void println(const std::string& message) {
        // Wypisanie komunikatu (możesz dostosować do swoich potrzeb)
        std::cout << message << std::endl;
    }

    void write(const uint8_t* data, size_t size) {
        // Symulacja przesyłania danych przez port szeregowy
        // Możesz dostosować tę część w zależności od implementacji
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "Data sent: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << static_cast<int>(data[i]) << " ";
        }
        std::cout << std::endl;
    }

    size_t available() {
        // Symulacja dostępności danych w buforze
        // Możesz dostosować tę część w zależności od implementacji
        return 0;
    }

    size_t readBytes(uint8_t* buffer, size_t length) {
        // Symulacja odczytu danych z portu szeregowego
        // Możesz dostosować tę część w zależności od implementacji
        return 0;
    }
};

RH_RF95<SerialPort> rf95;

void setup() {
    SerialUSB().begin(115200);
    SerialUSB().println("RF95 client test.");

    if (!rf95.init()) {
        SerialUSB().println("init failed");
        std::terminate();
    }

    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
    rf95.setFrequency(868.0);
}

void loop() {
    SerialUSB().println("Sending to rf95_server");
    // Send a message to rf95_server
    uint8_t data[] = "Hello World!";
    rf95.send(data, sizeof(data));

    rf95.waitPacketSent();

    // Now wait for a reply
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.waitAvailableTimeout(3000)) {
        // Should be a reply message for us now
        if (rf95.recv(buf, &len)) {
            SerialUSB().print("got reply: ");
            SerialUSB().println(reinterpret_cast<char*>(buf));
        } else {
            SerialUSB().println("recv failed");
        }
    } else {
        SerialUSB().println("No reply, is rf95_server running?");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main() {
    setup();
    while (true) {
        loop();
    }
    return 0;
}
