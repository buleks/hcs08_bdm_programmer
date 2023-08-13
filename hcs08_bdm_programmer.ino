#define BKGD A0
#define RESET A1


void bdm_txPrepare(void); //tri state data pin
void bdm_txFinish(void); //si

void setup() {
  // put your setup code here, to run once:
  pinMode(BKGD, OUTPUT);
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, LOW);
  digitalWrite(BKGD, LOW);
  Serial.begin(115200);

}
void waitEnter()
{
  while (1) 
  {
    if(Serial.available())
    {
      int c = (int)Serial.read(); 
      if(c == '\n') break;
    }
  }
}
void enter_background()
{
    digitalWrite(RESET, LOW);
    Serial.print("\nReset supply and press enter");
    waitEnter();
    digitalWrite(RESET, HIGH);
    delayMicroseconds(10);
    digitalWrite(BKGD, HIGH);
    pinMode(BKGD, INPUT);
    Serial.print("\nTarget should be in background mode");
}

void Sync_Command()
{
  pinMode(BKGD, OUTPUT);
  digitalWrite(BKGD, LOW);
  delayMicroseconds(50);
  digitalWrite(BKGD, HIGH);
  pinMode(BKGD, INPUT);
  //wait for falling slope
  while(digitalRead(BKGD) == HIGH){}
  unsigned long falling = micros();
  while(digitalRead(BKGD)== LOW){}
  unsigned long rising = micros();
  unsigned long sync_time = rising-falling;
  Serial.print("\nSync time:");
  Serial.print(sync_time);
  Serial.print("us");
  
}


#define BIT_CHANGE_DELAY asm("nop");asm("nop");asm("nop");asm("nop");
#define BIT_STATE_DURATION asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
inline void write_byte(uint8_t byte)
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

inline uint8_t read_byte(void)
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

uint8_t read_BDCSR(void)
{
 //BDC Status and control register
 //Coding structure
 //E4/SS
 noInterrupts();
 write_byte(0xe4);//1110-0100
 uint8_t bdcsr = read_byte();
 interrupts();
 Serial.print("\nBDCSR:");
 Serial.print(bdcsr,HEX);
 Serial.print("\nENBDM=");
 Serial.print((bdcsr&0x80)>>7);
 
 Serial.print("|BDMACT=");
 Serial.print((bdcsr&0x40)>>6);

 
 Serial.print("|BKPTEN=");
 Serial.print((bdcsr&0x20)>>5);

 Serial.print("|RTS=");
 Serial.print((bdcsr&0x10)>>4);

 Serial.print("|CLKSW=");
 Serial.print((bdcsr&0x08)>>3);

 Serial.print("|WS=");
 Serial.print((bdcsr&0x04)>>2);

 Serial.print("|WSF=");
 Serial.print((bdcsr&0x02)>>1);

 Serial.print("|DVF=");
 Serial.print((bdcsr&0x01));
 return bdcsr;

 
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
   noInterrupts();
   //0xe0 - 1110 0000
   write_byte(0xe0); //read byte from target memory
   write_byte((addr&0xff00)>>8); 
   write_byte(addr&0x00ff); 
   DLY //SHould be 16 BDCLK cycles
   uint8_t data = read_byte();
   interrupts();
   return data;
}
uint8_t write_BYTE(uint16_t addr,uint8_t data)
{
  noInterrupts();
  write_byte(0xc0); //write byte to target memory 1100 0000
  write_byte((addr&0xff00)>>8); //0x027F 0000 0010 
  write_byte(addr&0x00ff); //0111 1111
  write_byte(data);  // 1010 1010
  DLY //SHould be 16 BDCLK cycles
  interrupts();
}
uint8_t write_BYTE_WS(uint16_t addr,uint8_t data)
{
  noInterrupts();
  read_BDCSR();
  write_byte(0xc1); //write byte to target memory
  write_byte((addr&0xff00)>>8); 
  write_byte(addr&0x00ff);
  write_byte(data);  
  DLY //SHould be 16 BDCLK cycles
  DLY
  read_BDCSR();
  interrupts();
  

}

uint8_t read_A(void)
{
  noInterrupts();
  write_byte(0x68); 
  DLY
  uint8_t data = read_byte();
  interrupts();
  return data;
}

void write_A(uint8_t data)
{
  noInterrupts();
  write_byte(0x48); 
  write_byte(data); 
  DLY
  interrupts();
}
uint16_t read_HX(void)
{
  noInterrupts();
  write_byte(0x6C); 
  DLY
  uint8_t data1 = read_byte();
  uint8_t data2 = read_byte();
  interrupts();
  return ((data1<<8) | data2);
}

void write_HX(uint16_t data)
{
  noInterrupts();
  write_byte(0x4C); 
  write_byte((data&0xff00)>>8); 
  write_byte(data&0x00ff);
  DLY
  interrupts();
}

uint8_t read_NEXT(void)
{
  noInterrupts();
  write_byte(0x70); 
  DLY
  uint8_t data = read_byte();
  interrupts();
  return data;
}

void write_NEXT(uint8_t data)
{
  noInterrupts();
  write_byte(0x50); 
  write_byte(data); 
  DLY
  interrupts();
}

uint16_t read_target_identifier()
{
  //SDIDH and SDIDL
  //$1806 and $1807
  uint8_t sdih = read_BYTE(0x1806);
  uint8_t sdil = read_BYTE(0x1807);
  uint16_t result = sdil | sdih<<8;
//  Serial.print("\nSDIH:");
//  Serial.print(sdih,HEX);
//  Serial.print(" SDIL:");
//  Serial.print(sdil,HEX);
  return result;
  
}
void show_target_identifier()
{
  uint16_t sdi = read_target_identifier();
  Serial.print("\nTarget identifier:0x");
  Serial.print(sdi,HEX);
  uint16_t id = sdi&0x0fff;
  uint16_t revision = (sdi&0xf000)>>12;
  Serial.print("\nRevision:0x");
  Serial.print(revision,HEX);
  Serial.print(" Part identifier:0x");
  Serial.print(id,HEX);

  if(id == 0x14)
  {
     Serial.print("\nDevice: MC9S08SG8");
  }
  else
  {
     Serial.print("\nDevice: Unknown");
  }
  
  
}
void test_BYTE_RW(void)
{
  
  uint16_t addr = 0x0080;
  uint8_t data = 0xCC;

  write_BYTE(addr,data);
  uint8_t res = read_BYTE(addr);
  Serial.print("\nRAM result:");
  Serial.print(res,HEX);
  if(data == res)
  {
    Serial.print("\nRAM byte RW test OK");
  }
  else
  {
    Serial.print("\nRAM byte RW test failed");
  }
  
}

void test_Accumulator(void)
{
    uint8_t res = read_A();
    Serial.print("\nA:");
    Serial.print(res,HEX);
    write_A(0xAA);
    
    res = read_A();
    Serial.print("\nA_new:");
    Serial.print(res,HEX);
    

}

void test_HX(void)
{
    //read_BDCSR();
    uint16_t res = read_HX();
    Serial.print("\nHX:");
    Serial.print(res,HEX);
    write_HX(0xAAAA);
    
    res = read_HX();
    Serial.print("\nHX_new:");
    Serial.print(res,HEX);
    

}

void read_RAM()
{
  uint16_t ram_start = 0x0080;
  uint16_t ram_end = 0x027F;
  Serial.print("\nRAM content[512Bytes]:");
  write_HX(ram_start-1);
  uint8_t data;
  for(uint16_t i = ram_start;i < ram_end;i++)
  {
    if(i%16 == 0)
    {
      Serial.print("\n");
    }
    data = read_NEXT();
    Serial.print(data,HEX);
    Serial.print(" ");
   
  }

}

void write_RAM(uint8_t value)
{
  uint16_t ram_start = 0x0080;
  uint16_t ram_end = 0x027F;
  Serial.print("\nRAM content[512Bytes]:");
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
  Serial.print("\nRAM test 0x00: OK");
 }else
 {
    Serial.print("\nRAM test 0x00: FAILED");
 }

 write_RAM(0xFF);
 if(test_RAM(0xFF) == 0)
 {
  Serial.print("\nRAM test 0xFF: OK");
 }else
 {
    Serial.print("\nRAM test 0xFF: FAILED");
 }

 write_RAM(0xAA);
 if(test_RAM(0xAA) == 0)
 {
  Serial.print("\nRAM test 0xAA: OK");
 }else
 {
    Serial.print("\nRAM test 0xAA: FAILED");
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
  
  
  Serial.print("\nFLASH content[8kBytes]:");
  write_HX(flash_start-1);
  uint8_t data;
  for(uint16_t i = flash_start;i < flash_end;i++)
  {
    if(i%16 == 0)
    {
      Serial.print("\n");
      uint16_t current_addr = read_HX();
      Serial.print(current_addr+1,HEX);
      Serial.print(": ");
    }
    data = read_NEXT();
    Serial.print(data,HEX);
    Serial.print(" ");
   
  }

}

void flash_print_FOPT()
{
   
 uint8_t fopt = read_BYTE(FOPT);

 Serial.print("\nFOPT:");
 Serial.print(fopt,HEX);
 Serial.print("\nKEYEN=");
 Serial.print((fopt&0x80)>>7);
 
 Serial.print("|FNORED=");
 Serial.print((fopt&0x40)>>6);

 Serial.print("|SEC01=");
 Serial.print((fopt&0x02)>>1);

 Serial.print("|SEC00=");
 Serial.print((fopt&0x01));
}

void flash_print_FSTAT()
{
   
 uint8_t fstat = read_BYTE(FSTAT);
 Serial.print("\nFSTAT:");
 Serial.print(fstat,HEX);
 Serial.print("\nFCBEF=");
 Serial.print((fstat&0x80)>>7);
 
 Serial.print("|FCCF=");
 Serial.print((fstat&0x40)>>6);

 
 Serial.print("|FPVIOL=");
 Serial.print((fstat&0x20)>>5);

 Serial.print("|FACCERR=");
 Serial.print((fstat&0x10)>>4);

 Serial.print("|FBLANK=");
 Serial.print((fstat&0x04)>>2);
 
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

inline void flash_wait_FCBEF()
{
  uint8_t fstat ;
   do{
     
      //wait 4 cycles of flash clock, aasuming 150khz cycle=6.66us what gives 4*6.66=26,66
      delayMicroseconds(27);
     fstat = read_BYTE(FSTAT);
      
     Serial.print("\nWating FCBEF.");
   } while((fstat&0x80) == 0);
}
void flash_write_byte(uint16_t adress, uint8_t data)
{
   uint8_t fstat = read_BYTE(FSTAT);
   if(fstat&0x10) //FACCERR set
   {
    Serial.print("\nFACCERR set, should be cleared");
    return;
   }

   Serial.print("\nWating FCBEF to be one/ for FLASH buffer to be empty");
   flash_wait_FCBEF();

   Serial.print("\nFlash buffer empty.");
   //Wrtie to flash 
   write_BYTE(adress, data);

   write_BYTE(FCMD, 0x20);//BYTE PROGRAM

  write_BYTE(FSTAT,1<<7);//FCBEF set
  flash_wait_FCBEF();

  fstat = read_BYTE(FSTAT);   
  if( fstat&(1<<BIT_FPVIOL) )
  {
    Serial.print("\nFPVIOL- access to protected area. Write failed");
    return;
  }
  if( fstat&(1<<BIT_FACERR) )
  {
    Serial.print("\nFACERR- Error. Write failed");
    return;
  }

  if( fstat&(1<<BIT_FCCF) )
  {
    Serial.print("\nCommand complete");
  }else
  {
    Serial.print("\nCommand in progress");
  }
   
   
 //NOP to 0x9D
}
void flash_page_erase()
{
 //8rows 64 bytes each = 512 bytes for page
 //8kB flash have 16 pages
}
void flash_mass_erase()
{
   uint8_t fstat = read_BYTE(FSTAT);
   if(fstat&0x10) //FACCERR set
   {
    Serial.print("\nFACCERR set, should be cleared");
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
    Serial.print("\nFPVIOL- access to protected area. Write failed");
    return;
  }
  if( fstat&(1<<BIT_FACERR) )
  {
    Serial.print("\nFACERR- Error. Write failed");
    return;
  }

  if( fstat&(1<<BIT_FCCF) )
  {
    Serial.print("\nCommand Mass erase complete");
  }else
  {
    Serial.print("\nCommand Mass erase in progress");
  }
}
/////////////////////////////////////////////////////////////
///////////////////////FLASH/////////////////////////////////
/////////////////////////////////////////////////////////////

void loop() {

  enter_background();
  Serial.println("\nPres enter to generate sync");
  waitEnter();
  Sync_Command();
  
  read_BDCSR();
  show_target_identifier();
  
  while(1)
  {
   Serial.println("\nPres enter to read register");
   waitEnter();
   //test_Accumulator();
   //test_RAM_RW();
   //test_HX();
   check_RAM();
   //write_RAM(0xEE);
   //test_BYTE_RW();
   flash_read_print();
  // flash_init();
  // flash_write_byte(flash_start,0xAA);
  }
  
}
