#include "scene_display.h"
void display_reset(void) {
 unsigned int index;
 for(index=0;index<=3;index++)display_reset_background(index);
 g_display_control.control=0;
 g_display_control.flags=2;
}
