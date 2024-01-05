#ifndef __RAM__
#define __RAM__

void read_RAM(void);
void write_RAM(uint8_t value);
void write_values_to_RAM(uint8_t value);
uint8_t RAM_check_values(uint8_t value);

#endif