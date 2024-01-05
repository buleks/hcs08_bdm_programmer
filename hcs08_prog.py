import serial
from serial.serialutil import SerialException
import getopt
import sys
from threading import Thread
import time

stop = False

def read_serial(serial_handle):
    while stop == False:
        c = serial_handle.read()
        print(c.decode(), end='')

def usage():
    print("usage python hcs08_prog.py params")
    print("where params:")


if __name__ == '__main__':
    print("HCS08 programmer")
    erase_action = False
    tests_action = False

    try:
        opts, args = getopt.getopt(sys.argv[1:], "het", ["help", "erase", "tests"])
    except getopt.GetoptError as err:
        # print help information and exit:
        print(err)  # will print something like "option -a not recognized"
        usage()
        sys.exit(2)

    for o, a in opts:
        if o == "-e":
            erase_action = True
        if o == "-t":
            tests_action = True
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

    t = Thread(target=read_serial, args=[serial_handle])
    t.start()
    time.sleep(3)
    if erase_action:
        print("\nErasing flash starting.")
        serial_handle.write(bytes("erase\n", 'utf-8'))

    if tests_action:
        print("\nTarget tests starting.")
        serial_handle.write(bytes("tests\n", 'utf-8'))

    time.sleep(2)
    stop = True
    t.join()
    serial_handle.close()
    print("\n\r")