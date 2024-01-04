
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "flash.h"
#include "serial.h"
#include "bdm.h"

uint16_t read_target_identifier(void);
void show_target_identifier(void);

static FILE out_stream = FDEV_SETUP_STREAM(serial_send, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    DDRF = (1<<BKGD_PIN) | (1<<RESET_PIN) | (1<<TARGET_SUPPLY_PIN);
    PORTF = 0;
    set_RESET_low();
    set_BKGD_low();
    disable_target_supply(true);
    _delay_ms(100);
    disable_target_supply(false);

    serial_init();
    stdout = &out_stream;

    enter_background();
    sync_command();
    read_BDCSR();
    show_target_identifier();
    wait_command();

    return 0;
}

uint16_t read_target_identifier(void)
{
  //SDIDH and SDIDL
  //$1806 and $1807
  uint8_t sdih = read_BYTE(0x1806);
  uint8_t sdil = read_BYTE(0x1807);
  uint16_t result = sdil | sdih<<8;
  return result;
  
}

void show_target_identifier(void)
{
    uint16_t sdi = read_target_identifier();
    printf("\n\rTarget identifier:0x%x", sdi);
   
    uint16_t id = sdi&0x0fff;
    uint16_t revision = (sdi&0xf000)>>12;
    printf("\n\rRevision:0x%x", revision);
   
    printf(" Part identifier:0x%x", id);

    if(id == 0x14)
    {
        printf("\n\rDevice: MC9S08SG8");
    }
    else
    {
        printf("\n\rDevice: Unknown");
    }
}

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

