import serial
from serial.serialutil import SerialException




if __name__ == '__main__':
    print("HCS08 programmer")
    try:
        serial_handle = serial.Serial(
        port='/dev/ttyACM0',
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=3
        )
    except SerialException as e:
        print(e)
        exit(1)

    if not serial_handle.is_open:
        print("Port not opened")
        exit(1)

    line = serial_handle.read(1000)
    print(line.decode())

    serial_handle.close()