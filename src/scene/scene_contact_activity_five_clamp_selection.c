#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_clamp_selection(void)
{
 int *selected=&STATE->selected_column;
 int minimum=8-STATE->column_count;
 if(*selected<minimum)*selected=minimum;
 selected=&STATE->selected_row;
 minimum=8-STATE->column_heights[STATE->selected_column];
 if(*selected<minimum)*selected=minimum;
}
