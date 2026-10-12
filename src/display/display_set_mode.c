#include "scene_display.h"
void display_set_mode(unsigned short mode) {
 display_reset();
 g_display_control.control=mode|0x40;
 g_display_control.flags|=2;
}
