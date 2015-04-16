#include "util.h"
#include "message.h"
#include "display.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

extern const char NIBBLE_MODE;
extern const char TOGGLE;

void clear_display(char firstTime) {
   if (firstTime) {
      lcd_clear_display(NIBBLE_MODE);
   }
}

void one_shot(char firstTime) {
   while (firstTime) {
      if (BUTTON_PRESSED) {
         firstTime = FALSE;
         lcd_clear_display(NIBBLE_MODE);
         lcd_print(ALT_MESSAGE, NIBBLE_MODE);
      }
   }
}

void toggle(char firstTime) {
   while(TRUE) {
      while (BUTTON_PRESSED) {
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
