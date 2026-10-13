#ifndef DISPLAY_WINDOW_MOTION_H
#define DISPLAY_WINDOW_MOTION_H

#include "display_window.h"

/* A 28-byte axis view begins at window +4 or +32. */
struct DisplayWindowAxis {
    unsigned short flags, duration;
    unsigned char unknown_04[16];
    int first_target, last_target;
};
void display_begin_window_axis_move(unsigned int, unsigned int, int, int,
                                    unsigned int);

#endif
