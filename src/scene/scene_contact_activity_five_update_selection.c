#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_update_selection(void)
{
 int first=STATE->selected_column,second=STATE->selected_row;
 input_step_vertical_pressed((InputU32 *)&STATE->selected_row,8-STATE->column_heights[STATE->selected_column],7,1,0);
 input_step_horizontal_pressed((InputU32 *)&STATE->selected_column,8-STATE->column_count,7,1,0);
 if(STATE->selected_column!=first) {
  int *selected=&STATE->selected_row;
  int minimum=8-STATE->column_heights[STATE->selected_column];
  if(*selected<minimum)*selected=minimum;
  audio_play_animation_cue(210);
 }
 if(STATE->selected_row!=second)audio_play_animation_cue(210);
}
