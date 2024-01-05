#ifndef __RAM__
#define __RAM__

void RAM_read(void);
void RAM_write(uint8_t value);
void RAM_write_values(uint8_t value);
uint8_t RAM_check_values(uint8_t value);
void RAM_print(void);

#endif