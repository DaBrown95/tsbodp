#include "frame_oam.h"
void frame_reset_affine_slots(void) {
 unsigned int i;
 g_frame_affine_slot_count=0;
 for(i=0;i<32;i++) g_frame_affine_slots[i]=0;
}
asm(".align 2, 0");
