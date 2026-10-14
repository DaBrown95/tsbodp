#include "frame_placement_session.h"
unsigned char frame_placement_rotate(unsigned int turn)
{
 struct FramePoint requested,position;
 if(g_frame_placement_session.effect->unknown_0a!=141)turn=g_frame_placement_rotations[((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->direction][turn];
 else turn=((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->direction;
 ((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->direction=turn;
 requested.x=((short *)&g_frame_placement_session.preview->position.x)[1];
 requested.y=((short *)&g_frame_placement_session.preview->position.y)[1];
 frame_grid_project_effect_point(g_frame_placement_session.grid,&requested,turn,&position);
 frame_placement_update_graphic();
 frame_set_position(g_frame_placement_session.preview,position.x<<16,position.y<<16);
 return frame_placement_validate();
}

asm(".align 2,0");
