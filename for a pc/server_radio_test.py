import serial
import time

# Podaj nazwę portu szeregowego
serial_port = '/dev/ttyUSB0'  # Zmień na odpowiedni port szeregowy

# Utwórz obiekt dla portu szeregowego
ser = serial.Serial(serial_port, 115200, timeout=1)

def receive_data():
    # Odczytaj dane z modułu LoRa
    data = ser.readline().decode('utf-8').strip()
    return data

try:
    while True:
        print("Oczekiwanie na dane...")
        received_data = receive_data()

        if received_data:
            print("Odebrano dane:", received_data)

        time.sleep(1)

except KeyboardInterrupt:
    pass
finally:
    ser.close()