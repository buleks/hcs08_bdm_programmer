#ifndef __SREC__
#define __SREC__

int srec_parse_line(char *line);
void srec_print_decoded(void);
void srec_write_flash(void);

#endif