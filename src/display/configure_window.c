#include "display.h"
#include "display_window.h"
void display_configure_window(unsigned int index, unsigned short inside, unsigned short outside) {
 if(index==0) {
  DISPLAY_REG16(0x04000048)=(DISPLAY_REG16(0x04000048)&0xff00)|inside;
  DISPLAY_REG16(0x0400004a)=(DISPLAY_REG16(0x0400004a)&0xff00)|outside;
 } else if(index==1) {
  /* Local mask/result allocation; both values finish at the immediate store. */
  register unsigned int selected asm("r1")=inside;
  register unsigned int combined asm("r0")=(*(volatile unsigned char *)0x04000048)|(selected<<8);
  DISPLAY_REG16(0x04000048)=combined;
  DISPLAY_REG16(0x0400004a)=(DISPLAY_REG16(0x0400004a)&0xff00)|outside;
 }
 display_enable_layers(g_display_window_enable_masks[index]);
}
asm(".align 2, 0");
