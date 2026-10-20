#include "display_window.h"
void display_configure_window_masks(unsigned short inside0,
 unsigned short inside1,unsigned short outside)
{
 volatile unsigned short *registers=(volatile unsigned short *)0x04000048;
 *registers=inside0 | (inside1<<8);
 registers++;
 *registers=(*registers&0xff00)|outside;
}
asm(".align 2,0");
