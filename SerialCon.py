import serial
import time
import psutil
import sys


def get_cpu_values() -> str:
    """recupere les valeur de temperature et de frequence du cpu
    Returns:
        tuple(int, float): (temp, freq)
    """
    supported_platforms = ["linux", "linux2",
                           "freebsd7", "freebsd8", "freebsd9"]
    platform = sys.platform
    freq = psutil.cpu_freq(
        percpu=True) if platform in supported_platforms else psutil.cpu_freq()
    temp = psutil.sensors_temperatures()
    return f"{temp} {str(freq)var:.2f}"


def get_fan_values() -> str:
    """recupere les valeur de vitesse de rotation des ventilateurs
    et la consommation electrique en watt

    Returns:
        tuple(int, int): (RPM, watt)
    """

    return "242 252"


def get_ram_values() -> str:
    """recupere les valeur de pourcentage d'utilisation de la ram
    et la taille de la ram en Go
    Returns:
        tuple(int, float): (percent, total)
    """
    ram = psutil.virtual_memory()
    ram_percent = ram.percent
    ram_total = ram.total / (1024 ** 3)
    return f"{ram_percent} {ram_total:.2f}"


def get_wifi_values() -> str:
    """recupere les valeur d'upload et de download de la connexion wifi

    Returns:
        (float, float): (upload, download)
    """
    up, down = psutil.net_io_counters()[:2]
    return f"{up/1024**2} {down/1024**2}"


def get_serial_port() -> str:
    """Récupère le port série à utiliser en fonction 
    du système d'exploitation

    Returns:
        str: le port série à utiliser
    """
    system = sys.platform
    unix_like = ["linux", "linux2", "Darwin"]
    if system in unix_like:
        return "/dev/ttyACM0"
    else:
        return "COMx"


def main():
    port = get_serial_port()

    while True:
        cpu_value = get_cpu_values().split(' ')
        fan_value = get_fan_values().split(' ')
        ram_value = get_ram_values().split(' ')
        wifi_value = get_wifi_values().split(' ')

        data_to_send = f"{cpu_value[0]} {cpu_value[1]} {fan_value[0]} {fan_value[1]} {ram_value[0]} {ram_value[1]} {wifi_value[0]} {wifi_value[1]}"
        print(data_to_send)

        try:
            with serial.Serial(port, baudrate=9600, timeout=1) as ser:
                ser.write(data_to_send.encode())
        except serial.SerialException as e:
            print(f"Error: {e}")

        time.sleep(12)


if __name__ == "__main__":
    main()
