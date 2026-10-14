#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_step_gauge(struct FrameObject *base) {
 int percent=0,frame;
 if(STATE->amount==0)frame_set_animation_frame((struct FrameTickObject*)base,0);
 else {
  switch(base->unknown_0a) {
  case 0:percent=save_world_ratio_percent(STATE->amount,g_scene_contact_activity_six_options[STATE->option].first_threshold);break;
  case 1:percent=save_world_ratio_percent(STATE->amount,g_scene_contact_activity_six_options[STATE->option].second_threshold);break;
  case 2:percent=save_world_ratio_percent(STATE->amount,g_scene_contact_activity_six_options[STATE->option].third_threshold);break;
  }
  frame=save_world_scale_percent(16,(unsigned short)percent);
  if(frame==16)frame=15;
  if(frame!=((struct FrameTickObject*)base)->previous_frame)frame_set_animation_frame((struct FrameTickObject*)base,(unsigned char)frame);
 }
}
asm(".align 2,0");
