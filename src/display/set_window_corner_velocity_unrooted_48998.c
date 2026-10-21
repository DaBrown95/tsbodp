#include "display_window_motion.h"

void display_set_window_corner_velocity_unrooted_48998(unsigned int index,
 unsigned int corner, int x, int y)
{
 unsigned int address=(unsigned int)&g_window_states[index];
 unsigned int offset=corner*sizeof(struct DisplayWindowAxis);
 struct DisplayWindowAxis *pair;
 offset+=4;
 address+=offset;
 pair=(struct DisplayWindowAxis *)address;
 pair->step[0]=x;
 pair->step[1]=y;
 pair->flags|=2;
}
