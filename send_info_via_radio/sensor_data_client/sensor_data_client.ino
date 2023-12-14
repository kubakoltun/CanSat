#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <RH_RF95.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>

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

  rf95.setFrequency(868.0);


  Serial.begin(9600);
  while ( !Serial ) delay(100);   
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
  ShowSerial.println("Sending to rf95_server");

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(1013.25);

  char sensorData[50];
  snprintf(sensorData, sizeof(sensorData), "Temp=%.2f*C, Pres=%.2fPa, Alti=%.2fm", temperature, pressure, altitude);

  rf95.send((uint8_t*)sensorData, strlen(sensorData));
  rf95.waitPacketSent();

  ShowSerial.println(sensorData);

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

  delay(1000);
}
