#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_set_selection(int first,int second)
{
 unsigned int value=STATE->cells.rows[first][second]>>4;
 if(value) {
  scene_contact_activity_five_apply_selection(first,second,value,0);
  if((unsigned int)STATE->selected_count<=1)scene_contact_activity_five_reset_selection();
 }
}
