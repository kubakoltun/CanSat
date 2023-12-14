#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <RH_RF95.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>

//SoftwareSerial SSerial(0, 1); // RX, TX
//#define COMSerial SSerial1
//#define ShowSerial Serial
//RH_RF95<SoftwareSerial> rf95(COMSerial);



#define COMSerial Serial1
#define ShowSerial SerialUSB

RH_RF95<HardwareSerial> rf95(COMSerial);


#define BMP_SCK  (19)
#define BMP_MISO (18)
// #define BMP_MOSI (11)
// #define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

int led = 13;

void setup() {
  ShowSerial.begin(115200);
  ShowSerial.println("RF95 server test.");

  pinMode(led, OUTPUT);

  if (!rf95.init()) {
      ShowSerial.println("init failed");
      while (1);
  }
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  //rf95.setTxPower(13, false);

  rf95.setFrequency(868.0);


  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(1013.25);

  char sensorData[50];
  snprintf(sensorData, sizeof(sensorData), "Temperature=%.2f*C, Pressure=%.2fPa, Altitude=%.2fm", temperature, pressure, altitude);

  if (rf95.available()) {
        // Should be a message for us now
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);

        
        
        if (rf95.recv(buf, &len)) {
            digitalWrite(led, HIGH);

            ShowSerial.print("got request: ");
            ShowSerial.println((char*)buf);

            // Send a reply
            rf95.send((uint8_t*)sensorData, strlen(sensorData));
            rf95.waitPacketSent();
            ShowSerial.print("Sent a reply with sensor data: ");
            ShowSerial.println(sensorData);

            digitalWrite(led, LOW);
        } else {
            ShowSerial.println("recv failed");
        }
    }
}
