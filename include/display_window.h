#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "display.h"

extern const unsigned short g_display_window_enable_masks[];
void display_disable_window(unsigned int);
void display_enable_window(unsigned int);
void display_configure_window(unsigned int, unsigned short, unsigned short);
void display_set_window_rectangle(unsigned int, int, int, int, int);

void display_disable_window_layers(void);
void display_configure_window_masks(unsigned short, unsigned short, unsigned short);

#endif
