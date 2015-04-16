#ifndef DISPLAY_H
#define DISPLAY_H

#define BUTTON_PRESSED (PINB & (1 << BUTTON_CHECK))

static void clear_display(char firstTime);
void one_shot();
void toggle();

#endif
