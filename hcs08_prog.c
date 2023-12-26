
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

#define BKGD_PIN PF0 // Arduino A0
#define RESET_PIN PF1 //Arduino A1
#define TARGET_SUPPLY_PIN PF2 //Arduino A2

#define HIGH true
#define LOW false

typedef bool pinState;


void serial_init(void);
int serial_send( char data, FILE *stream);
uint8_t serial_receive(void);
void waitEnter(void);

void disable_target_supply(bool x);
void set_RESET_low(void);
void set_RESET_high(void);
void set_BKGD_low(void);
void set_BKGD_high(void);
void configure_BKGD_input(void);
void configure_BKGD_output(void);
pinState get_pin_state(uint8_t pin);

void enter_background(void);
void Sync_Command(void);

uint8_t read_BDCSR(void);

void write_BYTE(uint16_t addr,uint8_t data);
uint8_t read_BYTE(uint16_t addr);
void write_BYTE_WS(uint16_t addr,uint8_t data);

uint16_t read_target_identifier(void);
void show_target_identifier(void);
void flash_mass_erase(void);
void flash_write_byte(uint16_t adress, uint8_t data);
void flash_init(void);
void flash_print_FSTAT(void);
void flash_print_FOPT(void);
void flash_read_print(void);

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
    Sync_Command();
    read_BDCSR();
    show_target_identifier();

    return 0;
}

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

void Sync_Command(void)
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

void serial_init(void)
{
    //Arduino Atmega2560 uses PE0(RX0) i PE1(TX0)
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // set character data size to 8
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

    //9600, crystal 16Mhz UBRR = 16000000/(16*baudrate)-1
    UBRR0 = 103;
}

uint8_t serial_receive(void)
{
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

int serial_send( char data, FILE *stream)
{
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
    return 0;
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

/////////////////////////////////////////////////////////////
///////////////////////FLASH/////////////////////////////////
/////////////////////////////////////////////////////////////
#define FCDIV 0x1820
#define FOPT  0x1821
//0x1823-FCNFG
//0x1824-FPROT
#define FSTAT 0x1825
#define BIT_FCBEF 7
#define BIT_FCCF 6
#define BIT_FPVIOL 5
#define BIT_FACERR 4
#define FCMD  0x1826

//Tutaj trzeba wyczyscic bity SEC01 i SEC00 na 1:0 aby podczas resetu nie włączało się zabezpieczenie flasha i RAMU
//choć nie wiem czy to konieczne  bo nie robie debugera
//0xFFBF - NVOPT

const uint16_t flash_start = 0xE000;
const uint16_t flash_end = 0xFFFF;

void flash_read_print()
{
  
  
  printf("\nFLASH content[8kBytes]:");
  write_HX(flash_start-1);
  uint8_t data;
  for(uint16_t i = flash_start;i < flash_end;i++)
  {
    if(i%16 == 0)
    {
      printf("\n");
      uint16_t current_addr = read_HX();
      printf("%x: ",current_addr+1);
    }
    data = read_NEXT();
    printf("%x ", data);
   
  }

}

void flash_print_FOPT()
{
  uint8_t fopt = read_BYTE(FOPT);

  printf("\nFOPT: 0x%x", fopt);
  printf("\nKEYEN=%d", (fopt&0x80)>>7);
  printf("|FNORED=%d", (fopt&0x40)>>6);
  printf("|SEC01=%d", (fopt&0x02)>>1);
  printf("|SEC00=%d", (fopt&0x01));
}

void flash_print_FSTAT()
{
  uint8_t fstat = read_BYTE(FSTAT);
  printf("\nFSTAT: 0x%x", fstat);
  printf("\nFCBEF=%d", (fstat&0x80)>>7);
  printf("|FCCF=%d", (fstat&0x40)>>6);
  printf("|FPVIOL=%d", (fstat&0x20)>>5);
  printf("|FACCERR=%d", (fstat&0x10)>>4);
  printf("|FBLANK=%d", (fstat&0x04)>>2);
}

void flash_init()
{
 //set clock by writing FCDIV
 //fFCLK= 4.7MHz/(24+1) = 188khz
 write_BYTE(FCDIV, 24);
 flash_print_FOPT();
 flash_print_FSTAT();
 //NOP to 0x9D
}

static inline void flash_wait_FCBEF(void)
{
  uint8_t fstat ;
   do{
     
      //wait 4 cycles of flash clock, aasuming 150khz cycle=6.66us what gives 4*6.66=26,66
      _delay_us(27);
     fstat = read_BYTE(FSTAT);
      
     printf("\nWating FCBEF.");
   } while((fstat&0x80) == 0);
}

void flash_write_byte(uint16_t adress, uint8_t data)
{
   uint8_t fstat = read_BYTE(FSTAT);
   if(fstat&0x10) //FACCERR set
   {
    printf("\nFACCERR set, should be cleared");
    return;
   }

   printf("\nWating FCBEF to be one/ for FLASH buffer to be empty");
   flash_wait_FCBEF();

   printf("\nFlash buffer empty.");
   //Wrtie to flash 
   write_BYTE(adress, data);

   write_BYTE(FCMD, 0x20);//BYTE PROGRAM

  write_BYTE(FSTAT,1<<7);//FCBEF set
  flash_wait_FCBEF();

  fstat = read_BYTE(FSTAT);   
  if( fstat&(1<<BIT_FPVIOL) )
  {
    printf("\nFPVIOL- access to protected area. Write failed");
    return;
  }
  if( fstat&(1<<BIT_FACERR) )
  {
    printf("\nFACERR- Error. Write failed");
    return;
  }

  if( fstat&(1<<BIT_FCCF) )
  {
    printf("\nCommand complete");
  }else
  {
    printf("\nCommand in progress");
  }
   
   
 //NOP to 0x9D
}

void flash_mass_erase(void)
{
   uint8_t fstat = read_BYTE(FSTAT);
   if(fstat&0x10) //FACCERR set
   {
    printf("\nFACCERR set, should be cleared");
    return;
   }
   flash_wait_FCBEF();
   //Wrtie to flash 
   write_BYTE(flash_start, 0x00);

   write_BYTE(FCMD, 0x41);//Mass erase

  write_BYTE(FSTAT,1<<7);//FCBEF set
  flash_wait_FCBEF();

  fstat = read_BYTE(FSTAT);   
  if( fstat&(1<<BIT_FPVIOL) )
  {
    printf("\nFPVIOL- access to protected area. Write failed");
    return;
  }
  if( fstat&(1<<BIT_FACERR) )
  {
    printf("\nFACERR- Error. Write failed");
    return;
  }

  if( fstat&(1<<BIT_FCCF) )
  {
    printf("\nCommand Mass erase complete");
  }else
  {
    printf("\nCommand Mass erase in progress");
  }
}
/////////////////////////////////////////////////////////////
///////////////////////FLASH/////////////////////////////////
/////////////////////////////////////////////////////////////

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

