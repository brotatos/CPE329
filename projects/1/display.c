#include "util.h"
#include "message.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void clear_display(char firstTime) {
   if (firstTime) {
      lcd_clear_display(NIBBLE_MODE);
   }
}

void one_shot(char firstTime) {
   while (firstTime) {
      if (PINB & (1 << BUTTON_CHECK)) {
         firstTime = FALSE;
         lcd_clear_display(NIBBLE_MODE);
         lcd_print(ALT_MESSAGE, NIBBLE_MODE);
      }
   }
}

void toggle(char firstTime) {
   while(TRUE) {
      while (PINB & (1 << BUTTON_CHECK)) {
         clear_display(firstTime);
         if (firstTime) {
            lcd_print(ALT_MESSAGE, NIBBLE_MODE);
         }
         firstTime = FALSE;
      }

      if (!firstTime) {
         clear_display(firstTime = TRUE);
         lcd_print(DEFAULT_MESSAGE, NIBBLE_MODE);
      }
   }
}
