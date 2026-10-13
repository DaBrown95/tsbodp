#include "display_need_effect_progress.h"
void frame_need_effect_read_center(struct FrameObject *object,struct FramePoint *point)
{
 struct FramePoint first,second;
 frame_grid_coordinates_to_point(g_frame_registration,(struct FramePoint *)((unsigned char *)object+0x9c),&first);
 frame_grid_coordinates_to_point(g_frame_registration,(struct FramePoint *)((unsigned char *)object+0xa4),&second);
 point->x=(unsigned int)((first.x+second.x)/2)<<16;
 point->y=(unsigned int)((first.y+second.y)/2)<<16;
}
asm(".align 2, 0");
