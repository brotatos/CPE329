#ifndef DISPLAY_H
#define DISPLAY_H

#define BUTTON_PRESSED (PINB & (1 << BUTTON_CHECK))

void clear_display(char firstTime);
void one_shot(char firstTime);
void toggle(char firstTime);

#endif
