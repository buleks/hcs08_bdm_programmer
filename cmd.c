#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "serial.h"
#include "cmd.h"
#include "flash.h"
#include "bdm.h"
#include "tests.h"

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

void parse_commands(char *buffer)
{
    if(strcmp("erase", buffer) == 0)
    {
        printf("\nErase command");
        flash_mass_erase();
    }
    if(strcmp("tests", buffer) == 0)
    {
        printf("\nTests starting");
        test_Accumulator();
        test_HX();
    }
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
        parse_commands(rx_buffer);
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
