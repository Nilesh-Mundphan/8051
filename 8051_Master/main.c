#include "system.h"
#include "gpio.h"
#include "delay.h"
#include "lcd.h"
#include "serial.h"
void gpio_example(void)
{
	gpio_pin_mode(0,OUTPUT);
	while(1)
	{
		gpio_pin_write(0,HIGH);
		delay_ms(1000);
		gpio_pin_write(0,LOW);
		delay_ms(1000);
	}
}
void lcd_example(void)
{
	  gpio_pin_write(2,LOW); 
		lcd_init(4,5,6,7,1,3);
    lcd_clear();
    lcd_print_xy(0,0,"    MASTER    ");
    lcd_print_xy(0,1,"8051 Libraries");
	  while(1);
}
void main(void)
{
	serial_init(9600);
    serial_print("8051 Serial Test\r\n");
    while(1)
    {
        if(serial_available() > 0)
        {
            serial_write(serial_read());
        }
    }
}