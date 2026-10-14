#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_remove_marked_cells(void)
{
 int i;
 STATE->selected_count=0;
 audio_play_animation_cue(212);
 for(i=0;i<64;++i) {
  struct SceneContactActivityFiveObject *object=STATE->objects[i];
  if(object&&object->timer) {
   int row,column;
   STATE->objects[i]=0;
   object->phase=4;
   frame_set_animation_frame((struct FrameTickObject *)object,3);
   row=display_bios_remainder(object->cell,8);
   column=display_bios_div(object->cell,8);
   STATE->cells.rows[row][column]=0;
  }
 }
}
asm(".align 2, 0");
