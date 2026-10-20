#include "scene_contact_activity_three.h"
extern struct FrameVariantResource g_scene_contact_activity_three_line_animation;
void scene_contact_activity_three_ensure_line_slot(unsigned int index,int x,int y)
{
 struct FrameObject **slots=g_scene_contact_activity_three_slots.objects;
 struct FrameObject **slot=slots+index;
 struct FrameObject *object=*slot;
 if(object==0){
  object=frame_allocate_object(6);
  object->flags=9;
  frame_set_animation_record(object,&g_scene_contact_activity_three_line_animation);
  ((struct SceneContactActivityThreeObject*)object)->contact_mode=0;
  ((struct SceneContactActivityThreeObject*)object)->double_size=0;
  ((struct SceneContactActivityThreeObject*)object)->layer=0;
  ((struct SceneContactActivityThreeObject*)object)->palette=14;
 }
 frame_set_position(object,x,y);
 *slot=object;
}
__asm__(".align 2,0");
