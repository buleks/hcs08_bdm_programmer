#include <stdio.h>
#include <stdbool.h>
#include "bdm.h"
#include "ram.h"

void RAM_print(void)
{
  uint16_t ram_start = 0x0080;
  uint16_t ram_end = 0x027F;
  printf("\nRAM content[512Bytes]:");
  write_HX(ram_start-1);
  uint8_t data;
  for(uint16_t i = ram_start;i < ram_end;i++)
  {
    if(i%16 == 0)
    {
      printf("\n");
    }
    data = read_NEXT();
    printf("%x ", data);
   
  }

}

void RAM_write_values(uint8_t value)
{
  uint16_t ram_start = 0x0080;
  uint16_t ram_end = 0x027F;
  printf("\nRAM content[512Bytes]:");
  write_HX(ram_start-1);
  for(uint16_t i = ram_start;i < ram_end;i++)
  {
    write_NEXT(value);
  }

}

uint8_t RAM_check_values(uint8_t value)
{ 
  uint16_t ram_start = 0x0080;
  uint16_t ram_end = 0x027F;
  write_HX(ram_start-1);
  uint8_t data;
  for(uint16_t i = ram_start;i < ram_end;i++)
  {
    data = read_NEXT();
    if(data != value)
    {
      return 1;
    }
  }
  return 0;
}
