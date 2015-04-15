#ifndef MY_LCD_H
#define MY_LCD_H

#include "util.h"

void lcd_cmd(char cmd);
void lcd_init(void);
void lcd_return_home(void);
void lcd_clear_display(void);
void lcd_write(char character);
void lcd_print(char *str, int nibble_mode);


#endif
