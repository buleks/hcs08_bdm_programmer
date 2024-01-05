#include <stdio.h>
#include <stdbool.h>
#include "bdm.h"
#include "ram.h"


void read_RAM(void)
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

void write_RAM(uint8_t value)
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

uint8_t test_RAM(uint8_t value)
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

void check_RAM(void)
{
  write_RAM(0x00);
  if(test_RAM(0x00) == 0)
  {
    printf("\nRAM test 0x00: OK");
  }else
  {
    printf("\nRAM test 0x00: FAILED");
  }

  write_RAM(0xFF);
  if(test_RAM(0xFF) == 0)
  {
    printf("\nRAM test 0xFF: OK");
  }else
  {
      printf("\nRAM test 0xFF: FAILED");
  }

  write_RAM(0xAA);
  if(test_RAM(0xAA) == 0)
  {
    printf("\nRAM test 0xAA: OK");
  }else
  {
    printf("\nRAM test 0xAA: FAILED");
  }
  
}

