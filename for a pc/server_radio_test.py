from sx127x.LoRa import LoRa
from sx127x import MODE, BAND
import serial

# Podaj nazwę portu szeregowego
serial_port = '/dev/ttyUSB0'  # Zmień na odpowiedni port szeregowy (np. '/dev/ttyUSB6' dla COM6)

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