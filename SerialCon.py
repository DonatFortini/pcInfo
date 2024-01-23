import serial
import time
import platform
import psutil
import sys


def get_cpu_values() -> tuple(int, float):
    """recupere les valeur de temperature et de frequence du cpu
    Returns:
        tuple(int, float): (temp, freq)
    """
    return "45,3.2"


def get_fan_values() -> tuple(int, int):
    """recupere les valeur de vitesse de rotation des ventilateurs
    et la consommation electrique en watt

    Returns:
        tuple(int, int): (RPM, watt)
    """

    return "242,252"


def get_ram_values() -> tuple(float, float):
    """recupere les valeur de pourcentage d'utilisation de la ram
    et la taille de la ram en Go
    Returns:
        tuple(float, float): (percent, total)
    """
    ram = psutil.virtual_memory()
    ram_percent = ram.percent
    ram_total = ram.total / (1024 ** 3)
    return f"{ram_percent:.2f},{ram_total:.2f}"


def get_wifi_values() -> tuple(float, float):
    """recupere les valeur d'upload et de download de la connexion wifi

    Returns:
        (float, float): (upload, download)
    """
    return "25.1,3.15"


def get_serial_port() -> str:
    """Récupère le port série à utiliser en fonction 
    du système d'exploitation

    Returns:
        str: le port série à utiliser
    """
    system = platform.system()
    if system == "Windows":
        return "COMx"
    elif system == "Linux" or system == "Darwin":
        return "/dev/ttyACM0"
    else:
        print(f"Unsupported operating system: {system}")
        sys.exit(1)


def main():
    port = get_serial_port()

    while True:
        cpu_value = get_cpu_values()
        fan_value = get_fan_values()
        ram_value = get_ram_values()
        wifi_value = get_wifi_values()

        data_to_send = f"CPU_{cpu_value[0]},{cpu_value[1]};FAN_{fan_value[0]},{fan_value[1]};RAM_{ram_value[0]},{ram_value[1]};WIFI_{wifi_value[0]},{wifi_value[1]};"
        print(data_to_send)

        try:
            with serial.Serial(port, baudrate=9600, timeout=1) as ser:
                ser.write(data_to_send.encode())
        except serial.SerialException as e:
            print(f"Error: {e}")

        time.sleep(12)


if __name__ == "__main__":
    main()
