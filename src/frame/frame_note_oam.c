#include "frame_render.h"
extern unsigned char *g_oam_previous;
void frame_note_oam(int index)
{
 struct FrameOam *bank=(struct FrameOam *)g_oam_previous;
 bank += 128;
 bank += index;
 bank->display_mode = 2;
}
asm(".align 2, 0");
