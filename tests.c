#include <stdio.h>
#include <stdbool.h>
#include "serial.h"
#include "flash.h"
#include "bdm.h"
#include "tests.h"

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