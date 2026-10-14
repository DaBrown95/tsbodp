#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
unsigned char scene_contact_activity_five_selection_finished(void)
{
 struct SceneContactActivityFiveObject *object=(struct SceneContactActivityFiveObject *)g_frame_primary_list.last;
 while(object) {
  struct SceneContactActivityFiveObject *previous=object->previous;
  if(object->id==1&&object->phase)return 0;
  object=previous;
 }
 return 1;
}
