#ifndef DISPLAY_WINDOW_MOTION_H
#define DISPLAY_WINDOW_MOTION_H

#include "display_window.h"

void display_begin_window_axis_move(unsigned int, unsigned int, int, int,
                                    unsigned int);

/* Step both coordinate records in one selected window. */
void display_step_window_axes(unsigned int);
void display_step_windows(void);

#endif
