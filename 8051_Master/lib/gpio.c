#include <REGX51.H>
#include "system.h"
#include "gpio.h"
void gpio_pin_mode(unsigned char pin,unsigned char mode)
{
	if (pin < 8)
	{
		if (mode==OUTPUT)
		{
			P0 &=~(1<<pin);
		}
		else if (mode==INPUT)
		{
			P0 |=(1<<pin);
		}
	}
}
void gpio_pin_write(unsigned char pin,unsigned char bit_val)
{
	if (pin<8)
	{
		if (bit_val==LOW)
		{
			P0 = P0 & ~(1<<pin);
		}
		else if (bit_val==HIGH)
		{
			P0 = P0 |(1<<pin);
		}
	}
	else if (pin<16)
	{
		pin-=8;
		if (bit_val==LOW)
		{
			P1 = P1 & ~(1<<pin);
		}
		else if (bit_val==HIGH)
		{
			P1 = P1 |(1<<pin);
		}
	}
	else if (pin<24)
	{
		pin-=16;
		if (bit_val==LOW)
		{
			P2 = P2 & ~(1<<pin);
		}
		else if (bit_val==HIGH)
		{
			P2 = P2 |(1<<pin);
		}
	}
  else if (pin<32)
	{
		pin-=34;
		if (bit_val==LOW)
		{
			P3 = P3 & ~(1<<pin);
		}
		else if (bit_val==HIGH)
		{
			P3 = P3 |(1<<pin);
		}
	}
}

unsigned char gpio_pin_read(unsigned char pin)
{
	if (pin<8)
	{
		return (((P0>>pin)&1));
	}
	else if (pin<16)
	{
		pin-=8;
		return (((P1>>pin)&1));
	}
	else if (pin<24)
	{
		pin-=16;
		return (((P2>>pin)&1));
	}
	else if (pin<32)
	{
		pin-=24;
		return (((P3>>pin)&1));
	}
return 0;	
}