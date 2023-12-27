import serial
from serial.serialutil import SerialException
import getopt
import sys


def usage():
    print("usage python hcs08_prog.py params")
    print("where params:")

if __name__ == '__main__':
    print("HCS08 programmer")


    erase_action = False
    try:
        opts, args = getopt.getopt(sys.argv[1:], "he", ["help", "erase"])
    except getopt.GetoptError as err:
        # print help information and exit:
        print(err)  # will print something like "option -a not recognized"
        usage()
        sys.exit(2)

    for o, a in opts:
        if o == "-e":
            erase_action = True
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        else:
            assert False, "unhandled option"

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
        sys.exit(1)

    if not serial_handle.is_open:
        print("Port not opened")
        exit(1)

    line = serial_handle.read(1000)
    print(line.decode())
    if erase_action:
        print("Erasing flash starting.")
        serial_handle.write(bytes("erase\n", 'utf-8'))

    serial_handle.close()