#ifndef TSBODP_TRANSITION_SINGLE_WINDOWS_H
#define TSBODP_TRANSITION_SINGLE_WINDOWS_H

/* Observed single-window transitions; selector and table populations remain open. */
void transition_grow_vertical_window(unsigned short targets);
void transition_grow_horizontal_window(unsigned short targets);
void transition_grow_vertical_window_from_bottom(unsigned short targets);
void transition_grow_horizontal_window_from_right(unsigned short targets);

void transition_shrink_vertical_window(unsigned short targets);
void transition_shrink_horizontal_window(unsigned short targets);

#endif
