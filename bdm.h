#ifndef __BDM__
#define __BDM__

#define BKGD_PIN PF0 // Arduino A0
#define RESET_PIN PF1 //Arduino A1
#define TARGET_SUPPLY_PIN PF2 //Arduino A2

#define HIGH true
#define LOW false

typedef bool pinState;

void disable_target_supply(bool x);
void set_RESET_low(void);
void set_RESET_high(void);
void set_BKGD_low(void);
void set_BKGD_high(void);
void configure_BKGD_input(void);
void configure_BKGD_output(void);
pinState get_pin_state(uint8_t pin);

void enter_background(void);
void sync_command(void);

uint8_t read_BDCSR(void);

void write_BYTE(uint16_t addr,uint8_t data);
uint8_t read_BYTE(uint16_t addr);
void write_BYTE_WS(uint16_t addr,uint8_t data);

uint16_t read_HX(void);
uint8_t read_NEXT(void);
void write_HX(uint16_t data);
void write_NEXT(uint8_t data);

#endif