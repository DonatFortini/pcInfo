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
    temp = temp[list(temp.keys())[0]][0].current
    freq = freq[0].current if platform in supported_platforms else freq.current
    return f"{temp} {freq/1000:.1f}"


def get_fan_values() -> str:
    """recupere les valeur de vitesse de rotation des ventilateurs
    et la consommation electrique en watt

    Returns:
        tuple(int, float): (RPM, watt)
    """
    fan = psutil.sensors_fans()
    if fan == {}:
        return "-1 0"
    sum_values = [i.current for i in fan[list(fan.keys())[0]]]
    sorted_values = sorted(sum_values)
    return f"{sorted_values[len(sorted_values)//2]} {len(sorted_values) * 0.5}"


def get_ram_values() -> str:
    """recupere les valeur de pourcentage d'utilisation de la ram
    et la taille de la ram en Go
    Returns:
        tuple(int, float): (percent, total)
    """
    ram = psutil.virtual_memory()
    ram_percent = ram.percent
    ram_total = ram.total / (1024 ** 3)
    return f"{ram_percent} {ram_total:.1f}"


def get_wifi_values() -> str:
    """recupere les valeur d'upload et de download de la connexion wifi

    Returns:
        (float, float): (upload, download)
    """
    up, down = psutil.net_io_counters()[:2]
    up = f"{up/1024**2:.1f}" if up/1024**2 % 100 == up / \
        1024**2 else f"{float(int(up/1024**2))}"
    down = f"{down/1024**2:.1f}" if down/1024**2 % 100 == down / \
        1024**2 else f"{float(int(down/1024**2))}"
    return f"{up} {down}"


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
    with serial.Serial(port, baudrate=9600, timeout=1) as ser:
        while ser.isOpen():
            cpu_value = get_cpu_values().split(' ')
            fan_value = get_fan_values().split(' ')
            ram_value = get_ram_values().split(' ')
            wifi_value = get_wifi_values().split(' ')
            data_to_send = f"{cpu_value[0]} {cpu_value[1]} {fan_value[0]} {fan_value[1]} {ram_value[0]} {ram_value[1]} {wifi_value[0]} {wifi_value[1]}"

            try:
                ser.write(data_to_send.encode())
            except Exception as e:
                print(f"Error: {e}")

            time.sleep(2)


if __name__ == "__main__":
    main()
