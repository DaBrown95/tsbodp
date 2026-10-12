#include "irq.h"
#include "transition_alpha.h"

void transition_tick_alpha_waves(void) {
 unsigned short a, b;
 g_transition_alpha_a.value += g_transition_alpha_a.step;
 if (g_transition_alpha_a.value <= g_transition_alpha_a.minimum) {
  g_transition_alpha_a.value = g_transition_alpha_a.minimum;
  g_transition_alpha_a.step = -g_transition_alpha_a.step;
 } else if (g_transition_alpha_a.value >= g_transition_alpha_a.maximum) {
  g_transition_alpha_a.value = g_transition_alpha_a.maximum;
  g_transition_alpha_a.step = -g_transition_alpha_a.step;
 }
 g_transition_alpha_b.value += g_transition_alpha_b.step;
 if (g_transition_alpha_b.value <= g_transition_alpha_b.minimum) {
  g_transition_alpha_b.value = g_transition_alpha_b.minimum;
  g_transition_alpha_b.step = -g_transition_alpha_b.step;
 } else if (g_transition_alpha_b.value >= g_transition_alpha_b.maximum) {
  g_transition_alpha_b.value = g_transition_alpha_b.maximum;
  g_transition_alpha_b.step = -g_transition_alpha_b.step;
 }
 a = g_transition_alpha_a.value >> 8;
 b = g_transition_alpha_b.value >> 8;
 g_transition_alpha_a.value = a << 8;
 g_transition_alpha_b.value = b << 8;
 REG16(0x04000052) = a | (b << 8);
}
