#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
unsigned char scene_contact_activity_five_has_adjacent_pair(void)
{
 int i,j;
 for(i=8-STATE->column_count;i<8;++i) {
  for(j=8-STATE->column_heights[i];j<8;++j) {
   unsigned int value=STATE->cells.rows[i][j];
   if(i>8-STATE->column_count&&STATE->cells.rows[i-1][j]==value)return 1;
   if(i<7&&STATE->cells.rows[i+1][j]==value)return 1;
   if(j>8-STATE->column_heights[i]&&STATE->cells.rows[i][j-1]==value)return 1;
   if(j<7&&STATE->cells.rows[i][j+1]==value)return 1;
  }
 }
 return 0;
}
