#ifndef __SERIAL_
#define __SERIAL__

void serial_init(void);
int serial_send( char data, FILE *stream);
void serial_send_buffer(char *buffer, uint8_t len);
uint8_t serial_receive(void);
void waitEnter(void);
void wait_command(void);
uint8_t serial_read_line(char *line_buffer);

#endif