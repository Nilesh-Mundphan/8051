#ifndef SERIAL_H_
#define SERIAL_H_

void serial_init(unsigned int baud_rate);
void serial_write(char ch);
void serial_print(const char *str);
unsigned int serial_available(void);
char serial_read(void);
void serial_flush(void);
void serial_interrupt(void);
void serial_responce(char *str,int timeout);


#endif	/* SERIAL_H */