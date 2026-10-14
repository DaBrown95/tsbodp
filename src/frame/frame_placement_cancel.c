#include "frame_placement_session.h"
void frame_placement_cancel(void)
{
 if(((struct FramePlacementActor *)g_frame_placement_session.actor)->mode==1)frame_remove_object(g_frame_placement_session.effect);
 else frame_enable_object_flags(g_frame_placement_session.effect,1);
 transition_configure_view((struct TransitionViewObject *)g_frame_placement_session.actor,*(const struct FramePoint *)g_transition_view_configuration,0);
 transition_set_view_origin(g_frame_placement_session.preview->position,0);
 frame_remove_object(g_frame_placement_session.preview);
 g_frame_placement_session.effect=0;
 g_frame_placement_session.actor=0;
 g_frame_placement_session.grid=0;
 g_frame_placement_session.preview=0;
 ((unsigned char *)&g_frame_placement_session.selected)[0]=0;
 ((unsigned char *)&g_frame_placement_session.selected)[1]=0;
 ((unsigned char *)&g_frame_placement_session.original_cell)[0]=0;
 ((unsigned char *)&g_frame_placement_session.original_cell)[1]=0;
}

asm(".align 2,0");
