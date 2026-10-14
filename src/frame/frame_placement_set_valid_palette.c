#include "frame_placement_session.h"
void frame_placement_set_valid_palette(unsigned char valid)
{
 if(valid==1)frame_acquire_palette_slot(g_frame_placement_session.preview,6);
 else frame_acquire_palette_slot(g_frame_placement_session.preview,1);
}

asm(".align 2,0");
