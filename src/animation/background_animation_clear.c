#include "background_animation.h"
extern void memory_fill(void *, int, unsigned int);

void background_animation_clear(void) {
 memory_fill(&g_background_animation, 0, 16);
}
