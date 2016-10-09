#include "system.h"
#include "delay.h"
#include "gpio.h"
#include "lcd.h"

uint8_t lcd_data_pins[4]={0,0,0,0};
uint8_t RS=0;
uint8_t EN=0;

void lcd_clk(void)
{
}

void lcd_init(int d4,int d5,int d6,int d7,int rs,int en)
{
    uint8_t i;
    lcd_data_pins[0]=d4;
	lcd_data_pins[1]=d5;
	lcd_data_pins[2]=d6;
	lcd_data_pins[3]=d7;
	RS=rs;
	EN=en;
    for (i=0;i<4;i++)
    {
        gpio_pin_mode(lcd_data_pins[i],OUTPUT);
    }
  
        gpio_pin_mode(RS,OUTPUT);
        gpio_pin_mode(EN,OUTPUT);
  
    lcd_send(0x03,LOW);
    lcd_send(0x02,LOW);
    lcd_send(0x28,LOW);
    lcd_send(0x0C,LOW);
    lcd_send(0x01,LOW);
    lcd_send(0x06,LOW);
    lcd_send(0x80,LOW);
}

void lcd_clear(void)
{
    lcd_send(0x01,LOW);
    lcd_send(0x80,LOW);
}

void lcd_nibble(unsigned char nibble)
{
  uint8_t i;
  for (i=0;i<4;i++)
  {
      if((( nibble >> i) & HIGH) == HIGH)
      gpio_pin_write(lcd_data_pins[i], HIGH);
      else
      gpio_pin_write(lcd_data_pins[i], LOW);
  }
}

void lcd_send(uint8_t byte,uint8_t rs_pin)
{
    unsigned char high_nibble=0,low_nibble=0;
    high_nibble=byte >> 4;
    low_nibble=(byte & 0x0F);

    delay_ms(3);
    if(rs_pin==HIGH)
      gpio_pin_write(RS, HIGH);
    else
      gpio_pin_write(RS, LOW);

    lcd_nibble(high_nibble);
    gpio_pin_write(EN, HIGH);
    delay_ms(3);
    gpio_pin_write(EN, LOW);

    delay_ms(3);
    lcd_nibble(low_nibble);
    gpio_pin_write(EN, HIGH);
    delay_ms(3);
    gpio_pin_write(EN, LOW);
}

void lcd_print(const char *str)
{
    while(*str!='\0')
    {
		if (*str=='\r')
		{
			lcd_send(' ',HIGH);
			str++;
		}
		else if(*str=='\n')
		{
			//lcd_send(0xC0,LOW);
			lcd_send(' ',HIGH);
            str++;
		}
		else
		{
			lcd_send(*str++,HIGH);
		}
	}
    /*
    while(*str!='\0')
    {
        lcd_send(*str++,HIGH);
    }*/
}

void lcd_goto_xy(unsigned char x,unsigned char y)
{
    if(y==0)
      lcd_send(0x80+x,LOW);
    else if(y==1)
      lcd_send(0xC0+x,LOW);

}

void lcd_print_xy(unsigned char x,unsigned char y,const char *str)
{
    lcd_goto_xy(x,y);
    lcd_print(str);
}

