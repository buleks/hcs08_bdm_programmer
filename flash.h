#ifndef __FLASH__
#define __FLASH__

void flash_mass_erase(void);
void flash_write_byte(uint16_t adress, uint8_t data);
void flash_init(void);
void flash_print_FSTAT(void);
void flash_print_FOPT(void);
void flash_print_FPROT(void);
void flash_print_content(void);
void test_write_flash(void);
uint8_t flash_read_FOPT_register(void);
void flash_read_FSTAT(void);

extern const uint16_t flash_start;
extern const uint16_t flash_end;

#endif