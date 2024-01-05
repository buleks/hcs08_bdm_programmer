#include <stdio.h>
#include <stdbool.h>
#include "serial.h"
#include "flash.h"
#include "bdm.h"
#include "tests.h"
#include "ram.h"

void test_Accumulator(void)
{
  printf("\nAccumulator testing");
  uint8_t res = read_A();
  printf("\nA: %x", res);
  write_A(0xAA);

  res = read_A();
  printf("\nA_new: %x", res);
  if(res == 0xAA)
  {
    printf("\n\033[32mAcumulator write test OK\033[0m");
  }
  else
  {
    printf("\n\033[31mAcumulator write test FAIL\033[0m");
  }

}

void test_HX(void)
{
    printf("\nHX testing");
    //read_BDCSR();
    uint16_t res = read_HX();
    printf("\nHX: %x", res);
    write_HX(0xAAAA);
    
    res = read_HX();
    printf("\nHX_new: %x", res);
   
    if(res == 0xAAAA)
    {
        printf("\n\033[32mHX write test OK\033[0m");
    }
    else
    {
        printf("\n\033[31mHX write test FAIL\033[0m");
    }
}

void test_RAM(void)
{
    printf("\nRAM test starting");
    RAM_write_values(0x00);
    if(RAM_check_values(0x00) == 0)
    {
        printf("\n\n\033[32mRAM test 0x00: OK\033[0m");
    }else
    {
        printf("\n\033[31mRAM test 0x00: FAILED\033[0m");
    }

    RAM_write_values(0xFF);
    if(RAM_check_values(0xFF) == 0)
    {
        printf("\n\n\033[32mRAM test 0xFF: OK\033[0m");
    }else
    {
        printf("\n\033[31mRAM test 0xFF: FAILED\033[0m");
    }

    RAM_write_values(0xAA);
    if(RAM_check_values(0xAA) == 0)
    {
    printf("\n\n\033[32mRAM test 0xAA: OK\033[0m");
    }else
    {
    printf("\n\033[31mRAM test 0xAA: FAILED\033[0m");
    }
  
}

void test_write_flash(void)
{
    flash_init();
    flash_write_byte(flash_start,0xAA);
}