#include "display.h"
#include "display_window.h"
void display_disable_window(unsigned int index) {
 display_disable_layers(g_display_window_enable_masks[index]);
}
asm(".align 2, 0");
