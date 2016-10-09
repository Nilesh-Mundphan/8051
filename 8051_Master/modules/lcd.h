#ifndef LCD_H
#define	LCD_H

void lcd_init(int d4,int d5,int d6,int d7,int rs,int en);
void lcd_clear(void);
void lcd_clk(void);
void lcd_goto_xy(unsigned char x,unsigned char y);
void lcd_send(uint8_t byte,uint8_t rs_pin);
void lcd_print(const char *str);
void lcd_print_xy(unsigned char x,unsigned char y,const char *str);
    
#endif	/* LCD_H */