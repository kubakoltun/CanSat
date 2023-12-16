import serial
import RPi.GPIO as GPIO
from time import sleep

class LoRa:
    def __init__(self, serial_port, frequency, mode, tx_power, bandwidth, spreading_factor, coding_rate, verbose=False):
        self.ser = serial.Serial(serial_port, 115200)
        self.frequency = frequency
        self.mode = mode
        self.tx_power = tx_power
        self.bandwidth = bandwidth
        self.spreading_factor = spreading_factor
        self.coding_rate = coding_rate
        self.verbose = verbose

    def receive(self):
        # Tutaj dodaj kod do odbierania danych z modułu LoRa
        # Prawdopodobnie będzie to odczyt z self.ser.readline() lub podobnej metody

    def close(self):
        self.ser.close()

# Podaj nazwę portu szeregowego
serial_port = '/dev/ttyUSB0'  # Zmień na odpowiedni port szeregowy

# Konfiguracja parametrów LoRa
lora = LoRa(serial_port=serial_port, frequency=868e6, mode=MODE.SLEEP, tx_power=14, bandwidth=BAND.WIDE, spreading_factor=7, coding_rate=5, verbose=True)

try:
    while True:
        # Odbierz dane z urządzenia LoRa
        received_data = lora.receive()
        if received_data:
            print("Odebrano dane:", received_data)

except KeyboardInterrupt:
    pass
finally:
    lora.close()