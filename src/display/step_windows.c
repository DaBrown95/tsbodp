#include "display_window_motion.h"
void display_step_windows(void)
{
 unsigned int index;
 for(index=0;index<2;index++) display_step_window_axes(index);
}
asm(".align 2,0");
