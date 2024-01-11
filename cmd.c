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

static void wait_OK(void)
{
  int i = 0;
  char buf[4];
  buf[3]=0;
  while(1)
  {
      char c = serial_receive();
      if(c == '\n')
      {
        i = 0;
      }
      buf[i%3] = c;
      i++;
      if(strcmp("\nOK", buf) == 0)
      {
        break;
      }
  }
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

        //512*16=8kB
        for(uint16_t i = 0;i < 512;i++)
        {
          for(int x = 0; x < 16; x++) //iterates 0 to 15
          {
            buffer[x] = read_NEXT();
          }
          serial_send_buffer(buffer, 16);
          wait_OK();
        }
    }

    if(strcmp("write_flash", buffer) == 0)
    {
      printf("\nwrite_flash command starting");
      flash_init();
      printf("\nOK");
      while(1)
      {
        serial_read_line(line_buffer);
        if(srec_parse_line(line_buffer) < 0)
        {
          printf("\nFAIL");
          break;
        }
        srec_write_flash();
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
