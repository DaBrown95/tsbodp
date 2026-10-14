#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_populate(void)
{
 int i;
 for(i=0;i<8;++i)STATE->column_heights[i]=8;
 STATE->selected_column=0;
 STATE->selected_row=0;
 STATE->column_count=8;
 for(i=0;i<5;++i)STATE->timed[i].timer=frame_random_range(20,40);
 for(i=0;i<64;++i) {
  unsigned int subtype=(unsigned short)frame_random_bounded(g_scene_contact_activity_five_rows[STATE->option].subtype_count-1);
  int column=display_bios_div(i,8);
  int row=display_bios_remainder(i,8);
  struct SceneContactActivityFiveObject *object;
  ++STATE->timed[subtype].unknown04;
  object=(struct SceneContactActivityFiveObject *)scene_contact_activity_five_create_cell(subtype,(row<<4)+56,(column<<4)+20);
  STATE->objects[i]=object;
  object->cell=i;
  ++subtype;
  STATE->cells.rows[row][column]=subtype+(subtype<<4);
 }
}
asm(".align 2,0");
