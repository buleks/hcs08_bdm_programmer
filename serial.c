#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include "serial.h"


void serial_init(void)
{
    //Arduino Atmega2560 uses PE0(RX0) i PE1(TX0)
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // set character data size to 8
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    //9600, crystal 16Mhz UBRR = 16000000/(16*baudrate)-1
    UBRR0 = 103;
}

uint8_t serial_receive(void)
{
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

int serial_send( char data, FILE *stream)
{
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
    return 0;
}

void waitEnter(void)
{
    while(1)
    {
        char c = serial_receive();
        if(c == '\r')
        {
            break;
        }
    }
    printf("\n\rEnter pressed");
}

void wait_command(void)
{
  static char rx_buffer[100];
  static uint16_t index = 0;

  while(1)
  {
      char c = serial_receive();
      if(c == '\n')
      {
        index = 0;
        if(strcmp("erase", rx_buffer) == 0)
        {
          printf("\nErase command");
        }
        break;
      }
      rx_buffer[index] = c;
      index++;
      if(index > 99) 
      {
        index = 0;
      }
  }
}
