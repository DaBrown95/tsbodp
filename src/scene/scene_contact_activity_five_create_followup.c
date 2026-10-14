#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
struct FrameObject *scene_contact_activity_five_create_followup(void)
{
 int retry=1,x=0,y=0;
 struct SceneContactActivityFiveObject *object=(struct SceneContactActivityFiveObject *)frame_allocate_object(2);
 do {
  int row=frame_random_range(0,7);
  if((unsigned char)(STATE->column_heights[row]-1)<=6) {
   x=row;
   y=7-STATE->column_heights[row];
   retry=0;
  }
 }while(retry);
 frame_set_position((struct FrameObject *)object,(x<<20)+0x380000,(y<<20)+0x140000);
 object->contact_mode=0;
 object->double_size=0;
 object->layer=1;
 object->palette=1;
 object->flags=25;
 frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_five_followup_animation);
 object->on_step=scene_contact_activity_five_step_followup;
 object->cell=retry;
 object->timer=10;
 return (struct FrameObject *)object;
}
