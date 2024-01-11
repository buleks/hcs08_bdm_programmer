import serial
from serial.serialutil import SerialException
import getopt
import sys
from threading import Thread
import time
import signal
import bincopy

stop_read = False
exit_app = False
confirmed = False


def signal_handler(sig, frame):
    global stop_read
    global exit_app
    print('You pressed Ctrl+C! Exiting app.')
    stop_read = True
    exit_app = True

def read_serial(serial_handle):
    global confirmed
    buffer = bytearray()
    while stop_read == False:
        c = serial_handle.read()
        try:
            print(c.decode(), end='')
            sys.stdout.flush()
            if c.decode() == '\n':
                buffer = bytearray()
            buffer.extend(c)
            if buffer.decode() == "\nFinished":
                break
            if buffer.decode() == "\nOK":
                confirmed = True
        except UnicodeDecodeError as e:
            print(c, end='')
        

def usage():
    print("usage python hcs08_prog.py params")
    print("where params:")
    print("help - prints this text")
    print("-e --erase - erases target mcu flash")
    print("-t --test - run tests for target mcu and debug interface")
    print("--ram - prints target ram content")
    print("--flash - prints target flash content")
    print("--write_flash=file - writes srec file, to target flash memory")
    print("--verify=file - verify srec with target flash content")

if __name__ == '__main__':
    print("HCS08 programmer")
    signal.signal(signal.SIGINT, signal_handler)

    erase_action = False
    tests_action = False
    print_ram_action = False
    print_flash_action = False
    dump_flash_action = False
    write_flash_action = False
    verify_action = False
    file_name = None
    
    try:
        opts, args = getopt.getopt(sys.argv[1:], "het", ["help", "erase", "tests", "ram", "flash", "dump_flash", "write_flash=", "verify="])
    except getopt.GetoptError as err:
        # print help information and exit:
        print(err)  # will print something like "option -a not recognized"
        usage()
        sys.exit(2)

    for o, a in opts:
        if o == "-e":
            erase_action = True
        elif o == "-t":
            tests_action = True
        elif o == "--ram":
            print_ram_action = True
        elif o == "--flash":
            print_flash_action = True
        elif o == "--dump_flash":
            dump_flash_action = True
        elif o == "--write_flash":
            write_flash_action = True
            file_name = a
        elif o == "--verify":
            verify_action = True
            file_name = a
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        else:
            print(o)
            assert False, "unhandled option"

    try:
        serial_handle = serial.Serial(
        port='/dev/ttyACM0',
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
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

    if print_ram_action:
        serial_handle.write(bytes("print_ram\n", 'utf-8'))

    if print_flash_action:
        serial_handle.write(bytes("print_flash\n", 'utf-8'))

    if dump_flash_action:
        stop_read = True
        t.join()
        print("\nFlash reading started...")
        serial_handle.write(bytes("read_flash\n", 'utf-8'))
        serial_handle.timeout = 60
        
        flash_data = bytearray()
        for x in range(512):
            if exit_app == True:
                break
            data = serial_handle.read(size=16)
            
            flash_data+=bytearray(data)
            print(f"\r{x}/512")
            serial_handle.write(bytes("\nOK", 'utf-8'))
        print("\nFlash written to file flash_dump.bin")
     
        with open("flash_dump.bin", "wb") as binary_file:
            binary_file.write(flash_data)

    def wait_OK():
        while confirmed == False and stop_read == False:
                    pass

    if write_flash_action:
        print(f"\nWriting flash data from {file_name}")
        serial_handle.write(bytes("write_flash\n", 'utf-8'))
        wait_OK()
        with open(file_name) as fp:
            count = sum(1 for _ in fp)
            print(f"\nLines to transmit: {count}")
            fp.seek(0)
            line_num = 1
            for line in fp:
                if stop_read == True:
                    break
                confirmed  = False
                print(f"\nStatus: {line_num}/{count}")
                line_num += 1
                serial_handle.write(bytes(line, 'utf-8'))
                wait_OK()
        stop_read = True

    if verify_action:
        f = bincopy.BinFile()
        f.add_srec_file(file_name, overwrite = True)
        print(f.as_binary())

    t.join()
    serial_handle.close()
    print("\n\r")