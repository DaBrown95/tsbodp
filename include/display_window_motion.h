#ifndef DISPLAY_WINDOW_MOTION_H
#define DISPLAY_WINDOW_MOTION_H

#include "display_window.h"

void display_begin_window_axis_move(unsigned int, unsigned int, int, int,
                                    unsigned int);

/* Independently bounded setters; incoming callers remain unknown.
 * Defined backing uses window and corner indices 0..1. */
void display_set_window_corner_position_unrooted_48974(unsigned int,
    unsigned int, int, int);
void display_set_window_corner_velocity_unrooted_48998(unsigned int,
    unsigned int, int, int);

/* Step both coordinate records in one selected window. */
void display_step_window_axes(unsigned int);
void display_step_windows(void);

#endif
