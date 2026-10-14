#include "resource_conditions.h"
unsigned int frame_actor_indicator_kind(unsigned char actor)
{
 unsigned int group=0;
 unsigned char *display=g_condition_display_bits;
 for(;group<=14;++display,++group) {
  if(*display) {
   unsigned int bit=0;
   unsigned char flags=*display;
   register unsigned int *base asm("r1")=g_condition_kind_ids;
   unsigned int compare=actor+18;
   unsigned int mask=1;
   unsigned int row=group*8;
   unsigned int offset=row*4;
   unsigned int *ids=(unsigned int *)(offset+(unsigned int)base);
   for(;bit<=7;++ids,++bit) {
    if((flags>>bit)&mask) {
     unsigned int id=row+bit;
     if(*ids==compare) return id;
    }
   }
  }
 }
 return 255;
}
asm(".align 2, 0");
