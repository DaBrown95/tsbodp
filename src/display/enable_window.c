#include "display.h"
#include "display_window.h"
void display_enable_window(unsigned int index) { display_enable_layers(g_display_window_enable_masks[index]); }
asm(".align 2, 0");
