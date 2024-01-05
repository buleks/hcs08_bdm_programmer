
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

uint8_t read_SRS_register(void)
{
    const uint16_t SRS_address = 0x1800;
    uint8_t data = read_BYTE(SRS_address);
    printf("\nSRS(System Reset Status Register): 0x%x", data);
    printf("\nPOR=%d", (data&0x80)>>7);
    printf("|PIN=%d", (data&0x40)>>6);
    printf("|COP=%d", (data&0x20)>>5);
    printf("|ILOP=%d", (data&0x10)>>4);
    printf("|ILAD=%d", (data&0x08)>>3);
    printf("|0=%d", (data&0x04)>>2);
    printf("|LVD=%d", (data&0x02)>>1);
    printf("|0=%d", (data&0x01));
    return data;
}

void target_soft_reset(void)
{
    const uint16_t SBDFR_address = 0x1801;
    write_BYTE(SBDFR_address, 0x01);
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
    read_SRS_register();
    test_Accumulator();
}
