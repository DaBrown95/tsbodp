#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_apply_selection(int row,int column,unsigned int kind_arg,unsigned int delay_arg)
{
 unsigned char kind=kind_arg,delay=delay_arg;
 int code=STATE->cells.rows[row][column]>>4;
 if(code==kind) {
  scene_contact_activity_five_set_cell_timer(row,column,delay);
  ++STATE->selected_count;
  ++delay;
  STATE->cells.rows[row][column]>>=4;
  if(row>8-STATE->column_count)scene_contact_activity_five_apply_selection(row-1,column,code,delay);
  if(row<7)scene_contact_activity_five_apply_selection(row+1,column,code,delay);
  if(column>8-STATE->column_heights[row])scene_contact_activity_five_apply_selection(row,column-1,code,delay);
  if(column<7)scene_contact_activity_five_apply_selection(row,column+1,code,delay);
 }
}
