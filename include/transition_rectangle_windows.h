#ifndef TSBODP_TRANSITION_RECTANGLE_WINDOWS_H
#define TSBODP_TRANSITION_RECTANGLE_WINDOWS_H

/* Rectangle transitions; complete selector and table populations remain open. */
void transition_expand_rectangle_outside_window(unsigned short targets);
void transition_contract_rectangle_window(unsigned short targets);
void transition_contract_rectangle_inside_window(unsigned short targets);

#endif
