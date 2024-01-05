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
    printf("\n\033[32mAcumulator test OK\033[0m");
  }
  else
  {
    printf("\n\033[31mAcumulator test FAIL\033[0m");
  }

}