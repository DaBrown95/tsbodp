#include "display.h"
#include "display_window_motion.h"
void display_step_window_axes(unsigned int index)
{
 struct WindowState *window=&g_window_states[index];
 register struct DisplayWindowAxis *axis asm("r5");
 unsigned int i;
 for(i=0,axis=&window->axes[0];i<2;axis++,i++) {
  register unsigned short flags asm("r2")=axis->flags;
  if(flags&2) {
   register unsigned short count_field asm("r0")=axis->duration;
   register unsigned int duration asm("r1")=count_field;
   unsigned int remaining=count_field;
   if(duration) {
    if(duration>1) {
     register int current asm("r4");
     int target=axis->target[0];
     int difference=target-(current=axis->current[0].position);
     current+=display_divide(difference,axis->duration);
     axis->current[0].position=current;
     target=axis->target[1];
     difference=target-(current=axis->current[1].position);
     current+=display_divide(difference,axis->duration);
     axis->current[1].position=current;
    } else {
     axis->current[0].position=axis->target[0];
     axis->current[1].position=axis->target[1];
     { register unsigned short cleared asm("r0")=~2&flags;
       axis->flags=cleared; }
    }
    axis->duration=remaining-1;
   } else {
    axis->current[0].position+=axis->step[0];
    axis->current[1].position+=axis->step[1];
   }
   window->flags|=1;
  }
 }
}
asm(".align 2,0");
