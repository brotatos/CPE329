#ifndef DISPLAY_H
#define DISPLAY_H

// Button port on Port B
#define BUTTON_CHECK 3
#define BUTTON_PRESSED (PINB & (1 << BUTTON_CHECK))
#define DEFAULT_MESSAGE "Hello World"
#define ALT_MESSAGE "Project 1 done!"

static void clear_display(char firstTime);
void one_shot();
void toggle();

#endif
