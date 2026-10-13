#include "display.h"
#include "display_window_motion.h"
void display_begin_window_axis_move(unsigned int index,unsigned int axis,int first,int last,unsigned int duration)
{
 unsigned int address=(unsigned int)&g_window_states[index];
 unsigned int offset=axis*28;
 struct DisplayWindowAxis *pair;
 offset+=4;
 address+=offset;
 pair=(struct DisplayWindowAxis *)address;
 pair->first_target=first;
 pair->last_target=last;
 pair->duration=duration;
 pair->flags|=2;
}
asm(".align 2, 0");
