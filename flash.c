#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include "bdm.h"
#include "flash.h"

const uint16_t FCDIV=0x1820;
const uint16_t FOPT=0x1821;

//0x1823-FCNFG
//0x1824-FPROT
const uint16_t FSTAT=0x1825;
#define BIT_FCBEF 7
#define BIT_FCCF 6
#define BIT_FPVIOL 5
#define BIT_FACERR 4
const uint16_t FCMD =0x1826;
const uint16_t NVOPT = 0xFFBF;

//Tutaj trzeba wyczyscic bity SEC01 i SEC00 na 1:0 aby podczas resetu nie włączało się zabezpieczenie flasha i RAMU
//choć nie wiem czy to konieczne  bo nie robie debugera
//0xFFBF - NVOPT

const uint16_t flash_start = 0xE000;
const uint16_t flash_end = 0xFFFF;

const uint8_t ERROR = 0;
const uint8_t INFO = 1;
const uint8_t DEBUG = 2;

uint8_t log_level = INFO;

void logger(uint8_t level , char *str)
{
  if(level <= log_level)
  {
    printf(str);
  }
}

void flash_print_content()
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
      
     logger(DEBUG,"\nWaiting FCBEF.");
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

  logger(DEBUG,"\nWating FCBEF to be one, for FLASH buffer to be empty");
  flash_wait_FCBEF();
  logger(DEBUG, "\nFlash buffer empty.");
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
    logger(DEBUG,"\nCommand complete");
  }else
  {
    logger(DEBUG,"\nCommand in progress");
  }
   
   
 //NOP to 0x9D
}

void flash_read_FSTAT(void)
{
  uint8_t data = read_BYTE(FSTAT);
  printf("\nFSTAT Flash Status Register: %x", data);
  printf("\nFCBEF=%d", (data&0x80)>>7);
  printf("|FCCF=%d", (data&0x40)>>6);
  printf("|FPVIOL=%d", (data&0x20)>>5);
  printf("|FACERR=%d", (data&0x10)>>4);
  printf("|0=%d", (data&0x08)>>3);
  printf("|FBLANK=%d", (data&0x04)>>2);
  printf("|0=%d", (data&0x02)>>1);
  printf("|0=%d", (data&0x01));
}

void flash_unsecure(void)
{
  flash_wait_FCBEF(); //wait for buffer empty flag
  write_BYTE(flash_start, 0x00);
  write_BYTE(FCMD, 0x05);//blank check
  write_BYTE(FSTAT,1<<7);//FCBEF set
  flash_wait_FCBEF();
  uint8_t fstat = read_BYTE(FSTAT);
  if(fstat&0x04) //FBLANK set
  {
    printf("\nBlank page check completed");
  }
  else
  {
    printf("\nBlank check shows that flash is not clear");
    flash_read_FSTAT();
    return;
  }
    
   //NVOPT so SEC01:SEC00 = 1:0
  flash_write_byte(NVOPT,0b10);//unsecure mode
  flash_read_FOPT_register();
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
  flash_read_FSTAT();
  flash_unsecure();
}

uint8_t flash_read_FOPT_register(void)
{
    const uint16_t FOPT_address = 0x1821;
    uint8_t data = read_BYTE(FOPT_address);
    printf("\nFOPT Flash Option Register: 0x%x", data);
    printf("\nKEYEN=%d", (data&0x80)>>7);
    printf("|FNORED=%d", (data&0x40)>>6);
    printf("|-=%d", (data&0x20)>>5);
    printf("|-=%d", (data&0x10)>>4);
    printf("|-=%d", (data&0x08)>>3);
    printf("|-=%d", (data&0x04)>>2);
    printf("|SEC01=%d", (data&0x02)>>1);
    printf("|SEC00=%d", (data&0x01));
    return data;
}
/////////////////////////////////////////////////////////////
///////////////////////FLASH/////////////////////////////////
/////////////////////////////////////////////////////////////