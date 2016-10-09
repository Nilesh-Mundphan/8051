#include <REGX51.H>
#include <intrins.h>
#include "delay.h"

void delay_us(unsigned int cnt)
{
	while(cnt)
	{
		_nop_();
		cnt--;
	}
}

void delay_ms(unsigned int count) 
{   
	unsigned int i;		      // Keil v7.5a 
	while(count)
	{
		i = 115; 			 // 115	exact value
		while(i>0) 
		i--;
	count--;
	}
}