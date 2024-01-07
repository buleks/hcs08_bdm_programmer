#ifndef __SREC__
#define __SREC__

int srec_parse_line(char *line);
void srec_print_decoded(void);

extern uint8_t srec_data_count ;
extern uint16_t srec_data_address;
extern uint8_t srec_data_decoded[];

#endif