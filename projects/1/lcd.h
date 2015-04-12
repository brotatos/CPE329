#ifndef MY_LCD_H
#define MY_LCD_H

#include "util.h"

/* Public functions */
void lcd_init(void);
void lcd_return_home(void);
void lcd_clear_display(void);
void lcd_write(char character);

/* Private functions */
static void lcd_cmd(char cmd);

#endif
