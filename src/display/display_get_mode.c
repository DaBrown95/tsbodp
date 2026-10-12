#include "display.h"
unsigned short display_get_mode(void) {
 return g_display_control.control & 7;
}
asm(".align 2, 0");
