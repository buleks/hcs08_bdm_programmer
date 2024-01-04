#ifndef __SERIAL_
#define __SERIAL__

void serial_init(void);
int serial_send( char data, FILE *stream);
uint8_t serial_receive(void);
void waitEnter(void);
void wait_command(void);

#endif