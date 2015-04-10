#ifndef MY_LCD_H
#define MY_LCD_H

#define F_CPU 16000000

#define TRUE 1
#define FALSE 0

#define E_HIGH(f) (f |= 1)
#define RW_HIGH(f) (f |= 2)
#define RS_HIGH(f) (f |= 4)

#define E_LOW(f) (f &= 0b11111110)
#define RW_LOW(f) (f &= 0b11111101)
#define RS_LOW(f) (f &= 0b11111011)

void lcd_init(void);
static void lcd_cmd(char cmd);
static void lcd_write_char(char ch);
static void lcd_write_enable();
static void lcd_write_disable();

#endif
