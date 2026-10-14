#include "frame_placement_session.h"
unsigned char frame_placement_confirm(void)
{
 unsigned char result=frame_placement_validate();
 if(result==1) {
  transition_configure_view((struct TransitionViewObject *)g_frame_placement_session.actor,*(const struct FramePoint *)g_transition_view_configuration,0);
  transition_set_view_origin(g_frame_placement_session.preview->position,0);
  if(((struct FramePlacementActor *)g_frame_placement_session.actor)->mode==0)frame_unregister_need_effect(g_frame_placement_session.grid,g_frame_placement_session.effect);
  g_frame_placement_session.effect->position=g_frame_placement_session.preview->position;
  ((struct FrameNeedEffectObject *)g_frame_placement_session.effect)->direction=((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->direction;
  frame_configure_need_effect(g_frame_placement_session.effect,((struct FrameNeedEffectObject *)g_frame_placement_session.effect)->direction,((short *)&g_frame_placement_session.effect->position.x)[1],((short *)&g_frame_placement_session.effect->position.y)[1]);
  frame_placement_reset_parameter(g_frame_placement_session.effect);
  frame_update_need_effect(g_frame_placement_session.effect);
  frame_enable_object_flags(g_frame_placement_session.effect,1);
  frame_enable_object_flags(g_frame_placement_session.preview,2);
  g_frame_placement_session.preview=0;
  frame_disable_primary_object_flags(0x1000000);
 }
 return result;
}

asm(".align 2,0");
