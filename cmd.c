#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "serial.h"
#include "cmd.h"
#include "flash.h"
#include "bdm.h"
#include "tests.h"
#include "ram.h"
#include "srec.h"

char buffer[16];
char line_buffer[255];

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
        flash_init();
        flash_mass_erase();
        printf("\nFinished");
    }
    if(strcmp("tests", buffer) == 0)
    {
        printf("\nTests starting");
        test_Accumulator();
        test_HX();
        test_RAM();
        test_write_flash();
        printf("\nFinished");
    }
    if(strcmp("print_ram", buffer) == 0)
    {
      printf("\nprint_ram command starting");
      RAM_print();
      printf("\nFinished");
    }
    if(strcmp("print_flash", buffer) == 0)
    {
      printf("\nprint_flash command starting");
      flash_print_content();
      printf("\nFinished");
    }
    if(strcmp("read_flash", buffer) == 0)
    {
        write_HX(flash_start-1);

        for(uint16_t i = 0;i < 8192;i++)
        {
          if(i%16 == 0 && i > 1)
          {
            serial_send_buffer(buffer, 16);
          }
          buffer[i%16] = read_NEXT();
        }
    }

    if(strcmp("write_flash", buffer) == 0)
    {
      printf("\nwrite_flash command starting");
      printf("\nOK");
      while(1)
      {
        uint8_t len = serial_read_line(line_buffer);
        serial_send_buffer(line_buffer, len);
        if(srec_parse_line(line_buffer) < 0)
        {
          printf("\nFAIL");
          break;
        }
        printf("\nOK");
      }
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
