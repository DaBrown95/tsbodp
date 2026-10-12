#include "frame_oam.h"
void frame_enable_oam(int index) {
 { struct FrameOam *first=(struct FrameOam *)g_oam_previous;
 first += index;
 first->display_mode=0; }
 { struct FrameOam *bank;
 bank=(struct FrameOam *)g_oam_previous;
 bank += 128;
 bank += index;
 bank->display_mode=0; }
}
asm(".align 2, 0");
