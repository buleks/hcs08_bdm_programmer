#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "bdm.h"


#define BIT_CHANGE_DELAY asm("nop");asm("nop");asm("nop");asm("nop");
#define BIT_STATE_DURATION asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
static inline void write_byte(uint8_t byte)
{

  uint8_t bit = (byte>>(7)) & (0x01); //First MSB bit
  uint8_t portf_with_bit = 0 ; 
  if(bit == 0) 
  { 
    portf_with_bit =PORTF & ~(0x01);
  }
  else 
  { 
    portf_with_bit = PORTF | 0x01;
  }

  //Transmission start
  DDRF|= 0x01;

  //First bit - MSB - 8 bit
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  
  BIT_CHANGE_DELAY
  
  PORTF = portf_with_bit;
 
  BIT_STATE_DURATION

  //Bit transmission finished
  //digitalWrite(BKGD, HIGH);
  PORTF |= 0x01;
  //Empty time before starting new bit
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");  

  //Second bit - 7 bit
  bit = (byte>>(6)) & (0x01); 
  if(bit == 0) 
  { 
    portf_with_bit =PORTF & ~(0x01);
  }
  else 
  { 
    portf_with_bit = PORTF | 0x01;
  }

   PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  
  PORTF = portf_with_bit;
 
  BIT_STATE_DURATION

  //Bit transmission finished
  //digitalWrite(BKGD, HIGH);
  PORTF |= 0x01;
  //Empty time before starting new bit
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");  

  //Third bit - 6bit

    bit = (byte>>(5)) & (0x01); 
  if(bit == 0) 
  { 
    portf_with_bit =PORTF & ~(0x01);
  }
  else 
  { 
    portf_with_bit = PORTF | 0x01;
  }

   PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  
  PORTF = portf_with_bit;
 
  BIT_STATE_DURATION

  //Bit transmission finished
  //digitalWrite(BKGD, HIGH);
  PORTF |= 0x01;
  //Empty time before starting new bit
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");  

  //Fourth bit - 5bit

    bit = (byte>>(4)) & (0x01); 
  if(bit == 0) 
  { 
    portf_with_bit =PORTF & ~(0x01);
  }
  else 
  { 
    portf_with_bit = PORTF | 0x01;
  }

   PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  
  PORTF = portf_with_bit;
 
  BIT_STATE_DURATION

  //Bit transmission finished
  //digitalWrite(BKGD, HIGH);
  PORTF |= 0x01;
  //Empty time before starting new bit
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");  

  //Fifth bit - 4 bit

    bit = (byte>>(3)) & (0x01); 
  if(bit == 0) 
  { 
    portf_with_bit =PORTF & ~(0x01);
  }
  else 
  { 
    portf_with_bit = PORTF | 0x01;
  }

   PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  
  PORTF = portf_with_bit;
 
  BIT_STATE_DURATION

  //Bit transmission finished
  //digitalWrite(BKGD, HIGH);
  PORTF |= 0x01;
  //Empty time before starting new bit
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");  

  //Sixth bit - 3 bit

  bit = (byte>>(2)) & (0x01); 
  if(bit == 0) 
  { 
    portf_with_bit =PORTF & ~(0x01);
  }
  else 
  { 
    portf_with_bit = PORTF | 0x01;
  }

   PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  
  PORTF = portf_with_bit;
 
  BIT_STATE_DURATION
  
  //Bit transmission finished
  //digitalWrite(BKGD, HIGH);
  PORTF |= 0x01;
  //Empty time before starting new bit
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");  

  //Seventh bit - 2 bit

    bit = (byte>>(1)) & (0x01); 
  if(bit == 0) 
  { 
    portf_with_bit =PORTF & ~(0x01);
  }
  else 
  { 
    portf_with_bit = PORTF | 0x01;
  }

   PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  
  PORTF = portf_with_bit;
 
  BIT_STATE_DURATION

  //Bit transmission finished
  //digitalWrite(BKGD, HIGH);
  PORTF |= 0x01;
  //Empty time before starting new bit
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");  

  //Eight bit - 1 bit

  bit = byte&0x01; 
  if(bit == 0) 
  { 
    portf_with_bit =PORTF & ~(0x01);
  }
  else 
  { 
    portf_with_bit = PORTF | 0x01;
  }

   PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  
  PORTF = portf_with_bit;
 
  BIT_STATE_DURATION

  //Bit transmission finished
  //digitalWrite(BKGD, HIGH);
  PORTF |= 0x01;
  //Empty time before starting new bit
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");  
}

#define BIT_PROBE_DELAY asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
#define DELAY_AFTER_BIT_PROBE asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");

static inline uint8_t read_byte(void)
{
  uint8_t result =0;
  uint8_t pin = 0;

  //BKGD as output
  DDRF|= 0x01;


  //First reading bit
  //BKGD-LOW bit start MSB-7bit ; 
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  DDRF&= ~(0x01); //PF0(A0) as input
  //Probing shoud be 10 BDC clks from bit start
  //7 nops should give it
  BIT_PROBE_DELAY
  pin = PINF&0x01;
  result |= (pin << (7));
  //Empty time before starting new bit
  DELAY_AFTER_BIT_PROBE 

  //Second reading bit
  //BKGD-LOW bit start 6bit ; 
  DDRF |= 0x01;
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  DDRF&= ~(0x01); //PF0(A0) as input
  //Probing shoud be 10 BDC clks from bit start
  //7 nops should give it
  BIT_PROBE_DELAY
  pin = PINF&0x01;
  result |= (pin << (6));
  //Empty time before starting new bit
  DELAY_AFTER_BIT_PROBE 

  //Third reading bit
  //BKGD-LOW bit start 5bit ; 
  DDRF |= 0x01;
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  DDRF&= ~(0x01); //PF0(A0) as input
  //Probing shoud be 10 BDC clks from bit start
  //7 nops should give it
  BIT_PROBE_DELAY
  pin = PINF&0x01;
  result |= (pin << (5));
  //Empty time before starting new bit
  DELAY_AFTER_BIT_PROBE

  //Fourth reading bit
  //BKGD-LOW bit start 4bit ; 
  DDRF |= 0x01;
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  DDRF&= ~(0x01); //PF0(A0) as input
  //Probing shoud be 10 BDC clks from bit start
  //7 nops should give it
  BIT_PROBE_DELAY
  pin = PINF&0x01;
  result |= (pin << (4));
  //Empty time before starting new bit
  DELAY_AFTER_BIT_PROBE

  //Fith reading bit
  //BKGD-LOW bit start 3bit ;
  DDRF |= 0x01; 
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  DDRF&= ~(0x01); //PF0(A0) as input
  //Probing shoud be 10 BDC clks from bit start
  //7 nops should give it
  BIT_PROBE_DELAY
  pin = PINF&0x01;
  result |= (pin << (3));
  //Empty time before starting new bit
  DELAY_AFTER_BIT_PROBE

  //Sixth reading bit
  //BKGD-LOW bit start 2bit ; 
  DDRF |= 0x01;
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  DDRF&= ~(0x01); //PF0(A0) as input
  //Probing shoud be 10 BDC clks from bit start
  //7 nops should give it
  BIT_PROBE_DELAY
  pin = PINF&0x01;
  result |= (pin << (2));
  //Empty time before starting new bit
  DELAY_AFTER_BIT_PROBE

  //Seventh reading bit
  //BKGD-LOW bit start 1bit ; 
  DDRF |= 0x01;
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  DDRF&= ~(0x01); //PF0(A0) as input
  //Probing shoud be 10 BDC clks from bit start
  //7 nops should give it
  BIT_PROBE_DELAY
  pin = PINF&0x01;
  result |= (pin << (1));
  //Empty time before starting new bit
  DELAY_AFTER_BIT_PROBE

  //Eight reading bit
  //BKGD-LOW bit start 0bit ; 
  DDRF |= 0x01;
  PORTF &= ~(0x01);
   //wait 3 BDC clocks, to give time to target to recognise start of transmition
   //about 0.33us delay
  BIT_CHANGE_DELAY
  DDRF&= ~(0x01); //PF0(A0) as input
  //Probing shoud be 10 BDC clks from bit start
  //7 nops should give it
  BIT_PROBE_DELAY
  pin = PINF&0x01;
  result |= pin ;
  //Empty time before starting new bit
  DELAY_AFTER_BIT_PROBE
  
  return result;
}

#define DLY asm("nop");asm("nop");asm("nop");asm("nop"); \
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); \
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); \
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); \
        asm("nop");asm("nop"); \
        asm("nop");asm("nop");asm("nop");asm("nop"); \
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); \
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); \
        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop"); \
        asm("nop");asm("nop");
        
uint8_t read_BYTE(uint16_t addr)
{
//    noInterrupts();
   //0xe0 - 1110 0000
   write_byte(0xe0); //read byte from target memory
   write_byte((addr&0xff00)>>8); 
   write_byte(addr&0x00ff); 
   DLY //SHould be 16 BDCLK cycles
   uint8_t data = read_byte();
//    interrupts();
   return data;
}

void write_BYTE(uint16_t addr,uint8_t data)
{
//   noInterrupts();
  write_byte(0xc0); //write byte to target memory 1100 0000
  write_byte((addr&0xff00)>>8); //0x027F 0000 0010 
  write_byte(addr&0x00ff); //0111 1111
  write_byte(data);  // 1010 1010
  DLY //SHould be 16 BDCLK cycles
//   interrupts();
}

void write_BYTE_WS(uint16_t addr,uint8_t data)
{
//   noInterrupts();
  read_BDCSR();
  write_byte(0xc1); //write byte to target memory
  write_byte((addr&0xff00)>>8); 
  write_byte(addr&0x00ff);
  write_byte(data);  
  DLY //SHould be 16 BDCLK cycles
  DLY
  read_BDCSR();
//   interrupts();
}

uint8_t read_A(void)
{
  write_byte(0x68); 
  DLY
  uint8_t data = read_byte();
  return data;
}

void write_A(uint8_t data)
{
  write_byte(0x48); 
  write_byte(data); 
  DLY
}

uint16_t read_HX(void)
{
  write_byte(0x6C); 
  DLY
  uint8_t data1 = read_byte();
  uint8_t data2 = read_byte();
  return ((data1<<8) | data2);
}

void write_HX(uint16_t data)
{
  write_byte(0x4C); 
  write_byte((data&0xff00)>>8); 
  write_byte(data&0x00ff);
  DLY
}

uint8_t read_NEXT(void)
{
  write_byte(0x70); 
  DLY
  uint8_t data = read_byte();
  return data;
}

void write_NEXT(uint8_t data)
{
  write_byte(0x50); 
  write_byte(data); 
  DLY
}

void sync_command(void)
{
  configure_BKGD_output();
  set_BKGD_low();
  _delay_us(50); //should take at least 128 BDM cycles of target MCU
  set_BKGD_high();
  configure_BKGD_input();
  //Sync impulse is schort(less than 2us), therefore this code must be kept simple as is.
  uint8_t timeout1 = 0;
  uint8_t timeout2 = 0;
  while(get_pin_state(BKGD_PIN) == HIGH)
  {
    timeout1++;
    if(timeout1 > 1000)
    {
        printf("Sync rising edge not detected. Reset and try again.");
        while(true){}
    }
  }
  while(get_pin_state(BKGD_PIN)== LOW)
  {
    timeout2++;
    if(timeout2 > 1000)
    {
        printf("Sync falling edge not detected. Reset and try again.");
        while(true){}
    }
  }
  printf("\n\rSync received succesfully.");
}

void enter_background(void)
{
    set_RESET_low();
    _delay_ms(10);
    set_RESET_high();
    _delay_us(10);
    set_BKGD_high();
    configure_BKGD_input();
    printf("\n\rTarget should be in background mode");
}

inline pinState get_pin_state(uint8_t pin)
{
    uint8_t state = PINF & (1 << pin);
    if(state)
    {
        return HIGH;
    }
    else
    {
        return LOW;
    }
}

void disable_target_supply(bool x)
{
  if(x == true)
  {
    PORTF |= (1 << TARGET_SUPPLY_PIN);
  }
  else
  {
    PORTF &= ~(1 << TARGET_SUPPLY_PIN);
  }
}

void set_RESET_low(void)
{
    PORTF &= ~(1 << RESET_PIN);
}

void set_RESET_high(void)
{
    PORTF |= (1 << RESET_PIN);
}

void set_BKGD_low(void)
{
    PORTF &= ~(1 << BKGD_PIN);
}

void set_BKGD_high(void)
{
    PORTF |= (1 << BKGD_PIN);
}

void configure_BKGD_input(void)
{
      DDRF &= ~(1<<BKGD_PIN);
}

void configure_BKGD_output(void)
{
      DDRF |= (1<<BKGD_PIN);
}

uint8_t read_BDCSR(void)
{
    //BDC Status and control register
    //Coding structure
    //E4/SS
    // noInterrupts();
    write_byte(0xe4);//1110-0100
    uint8_t bdcsr = read_byte();
    // interrupts();
    printf("\n\rBDCSR: 0x%x",bdcsr);
    printf("\n\rENBDM=%d", (bdcsr&0x80)>>7);
    
    printf("|BDMACT=%d", (bdcsr&0x40)>>6);

    printf("|BKPTEN=%d", (bdcsr&0x20)>>5);

    printf("|RTS=%d", (bdcsr&0x10)>>4);

    printf("|CLKSW=%d", (bdcsr&0x08)>>3);

    printf("|WS=%d", (bdcsr&0x04)>>2);

    printf("|WSF=%d", (bdcsr&0x02)>>1);

    printf("|DVF=%d", (bdcsr&0x01));
    return bdcsr;
}