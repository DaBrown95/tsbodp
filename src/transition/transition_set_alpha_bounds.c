#include "transition_alpha.h"

void transition_set_alpha_bounds(int a_minimum, int a_maximum, int b_minimum, int b_maximum) {
 g_transition_alpha_a.minimum = a_minimum << 8;
 g_transition_alpha_a.maximum = a_maximum << 8;
 g_transition_alpha_b.minimum = b_minimum << 8;
 g_transition_alpha_b.maximum = b_maximum << 8;
}
