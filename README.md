# hcs08_bdm_programmer
Simple project to make programmer for HCS08 microcontroller using BDM (Background debug mode)interface.
It had been written for MC9S08SG8, it is tested only with this microcontroller at the moment.

Hardware
It uses Arduino Mega 2560 board to realise BDM debug interface.
Simple circuit is attached using universal board, to allow automatically reset power supply to enter background mode.

Software
All timing are software instruction related, therefore it can only work with default clock configuration for arduino board and amtega microcontrollers.
To compile just enter command: make
To program arduno board: make program
Path to serial device must be specified in makefile.

Target HCS08 microcontroller can be programmed using python script. Only accepted file format is SREC S19.
python hcs08_prog.py --write_flash=flash_file.s19

To compile following software tools were used:
- avr-gcc 13.2.0
- GNU Make 4.4.1
- avrdude 7.2
- python 3.11.6
- python-bincopy 20.0.0
- python-pyserial 3.5