#include "system.h"
#include "delay.h"
#include "serial.h"
#define RXBUFFERMAX 32

volatile char rxBuffer[RXBUFFERMAX];
volatile int rx_Buffer_Head=-1,rx_Buffer_Tail=-1;

void serial_init(unsigned int baud_rate)
{
	unsigned int BAUD;
	if(baud_rate == 9600)
		BAUD=0xFD;

	TMOD=0x20;
	TH1=BAUD;
	SCON=0x50;
	IE=0x90;
	TR1=1;
}

void serial_write(char ch)
{
	SBUF=ch;
	while(TI==0);
		TI=0;
}

void serial_print(const char *str)
{
    while(*str)
			serial_write(*str++);
}

unsigned int serial_available(void)
{
	if(rx_Buffer_Head==-1) 
			return 0;
	if(rx_Buffer_Head < rx_Buffer_Tail)
			return(rx_Buffer_Tail - rx_Buffer_Head + 1);
	else if(rx_Buffer_Head > rx_Buffer_Tail)
			return (RXBUFFERMAX - rx_Buffer_Head + rx_Buffer_Tail + 1);
	else
		return 1;
}
char serial_read(void)
{
    char ch;
		if(rx_Buffer_Head == -1)
		return 0;
	    ch=rxBuffer[rx_Buffer_Head];
	
		if(rx_Buffer_Head == rx_Buffer_Tail)
		{
				rx_Buffer_Head = rx_Buffer_Tail = -1;
		}
		else
		{
			rx_Buffer_Head++;
     	if(rx_Buffer_Head == RXBUFFERMAX)
			rx_Buffer_Head=0;
		}
	return ch;
}

void serial_flush(void)
{
		while(serial_available())
			serial_read();
}

void serial_interrupt(void) interrupt 4
{
	if(RI)
		{
	char rxData=SBUF;
			RI=0;
		if((rx_Buffer_Tail == RXBUFFERMAX-1 && (rx_Buffer_Head == 0)) || ((rx_Buffer_Tail + 1) == rx_Buffer_Head))
			{
				rx_Buffer_Head++;
			}
			
			if(rx_Buffer_Head == RXBUFFERMAX || rx_Buffer_Head == -1)
				rx_Buffer_Head=0;
			
			if(rx_Buffer_Tail == RXBUFFERMAX - 1) 
					rx_Buffer_Tail=0;
			else 
					rx_Buffer_Tail++;
			rxBuffer[rx_Buffer_Tail]=rxData;
		}
}

void serial_responce(char *str,int timeout){
    int delay=0,i=0;
	while(timeout > delay)
	{
		while(serial_available() > 0)
		{
			char ch=serial_read();
			str[i++]=ch;
		}
		delay_ms(1);
		delay++;
	}
	str[i]='\0';
 }
