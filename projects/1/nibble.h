#ifndef NIBBLE_H
#define NIBBLE_H

#include "util.h"

/* Public functions */
void nibble_lcd_init(void);
void nibble_lcd_return_home(void);
void nibble_lcd_clear_display(void);
void nibble_lcd_write(char character);

/* Private functions */
static void nibble_lcd_cmd(char cmd);

#endif
