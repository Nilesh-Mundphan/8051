#ifndef GPIO_H_
#define	GPIO_H_
    
void gpio_pin_mode(unsigned char pin,unsigned char mode);
void gpio_pin_write(unsigned char pin,unsigned char bit_val);
unsigned char gpio_pin_read(unsigned char pin);

#endif	/* GPIO_H */