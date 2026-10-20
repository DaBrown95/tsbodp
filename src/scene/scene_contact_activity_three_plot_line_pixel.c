#include "scene_contact_activity_three.h"
void scene_contact_activity_three_plot_line_pixel(unsigned short *buffer,int x,int y)
{
 int index,shift,mask;
 if(x<0)x=0;
 if(x>15)x=15;
 index=((y>>3)<<5)+((x>>3)<<4)+((y&7)<<1)+((x&7)>>2);
 shift=(x&3)<<2;
 mask=15<<shift;buffer[index]=(1<<shift)+(buffer[index]&~mask);
}
__asm__(".align 2,0");
