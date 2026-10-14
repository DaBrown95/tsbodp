#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
void scene_contact_activity_three_reset_row(struct FrameObject *base) {
 int scale=65536;
 if(((struct SceneContactActivityThreeObject*)base)->outcome==11) {
  frame_set_animation_record(base,&g_scene_contact_activity_three_row_definitions[((struct SceneContactActivityThreeObject*)base)->subtype].animation);
  ((struct FrameObject*)STATE->observer.address)->flags|=16;
 }else {
  if(((struct SceneContactActivityThreeObject*)base)->outcome==4)frame_set_animation_record(base,&g_scene_contact_activity_three_row_special_animations[g_scene_contact_activity_three_direction_frames[((struct SceneContactActivityThreeObject*)base)->direction]]);
  else frame_set_animation_record(base,&g_scene_contact_activity_three_row_normal_animations[g_scene_contact_activity_three_direction_frames[((struct SceneContactActivityThreeObject*)base)->direction]]);
  scene_contact_activity_three_queue_row_palette(base);
  frame_set_animation_frame((struct FrameTickObject*)base,(unsigned char)frame_random_range(0,((struct SceneContactActivityThreeObject*)base)->resource->sequence->frame_count-1));
 }
 ((struct SceneContactActivityThreeObject*)base)->frame_delay=g_scene_contact_activity_three_phase_definitions[((struct SceneContactActivityThreeObject*)base)->phase].frame_delay;
 scale=(int)((unsigned int)scale+(unsigned int)g_scene_contact_activity_three_phase_definitions[((struct SceneContactActivityThreeObject*)base)->phase].scale);
 scale=(int)((unsigned int)scale+(unsigned int)g_scene_contact_activity_three_background_entries[((struct SceneContactActivityThreeObject*)base)->palette_source].scale);
 scene_contact_activity_three_scale_row(base,scale,scale);
}
asm(".align 2,0");
