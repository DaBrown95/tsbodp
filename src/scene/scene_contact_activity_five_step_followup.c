#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_step_followup(struct FrameObject *base)
{
 struct SceneContactActivityFiveObject *object=(struct SceneContactActivityFiveObject *)base;
 switch(object->cell) {
 case 0:
  if(--object->timer==(unsigned int)-1) {
   int row,column;
   int i;
   audio_play_animation_cue(214);
   row=display_bios_div((short)(object->position.x>>16)-56,16);
   column=display_bios_div((short)(object->position.y>>16)-20,16);
   i=0;
   while(1) {
    if(i>=g_scene_contact_activity_five_rows[STATE->option].subtype_count-2)break;
    if(row-i>8-STATE->column_count) {
     int neighbor=row-1;
     int target=neighbor-i;
     if(STATE->cells.rows[target][column])scene_contact_activity_five_replace_cell(target,column);
    }
    if(row+i<7) {
     struct SceneContactActivityFiveState *state=STATE;
     int neighbor=row+1;
     int target=neighbor+i;
     if(state->cells.rows[target][column])scene_contact_activity_five_replace_cell(target,column);
    }
    if(column+i<7) {
     struct SceneContactActivityFiveState *state=STATE;
     int neighbor=column+1;
     int target=neighbor+i;
     if(state->cells.rows[row][target])scene_contact_activity_five_replace_cell(row,target);
    }
    ++i;
   }
   object->cell=1;
   object->timer=10;
   scene_contact_activity_five_rebuild_cells();
  }
  break;
 case 1:
  if(--object->timer==(unsigned int)-1) {
   STATE->flags&=~2;
   frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_five_followup_finish_animation);
   object->cell=5;
   audio_play_animation_cue(213);
  }
  break;
 case 5:
  if(object->flags&0x400000)object->flags|=2;
  break;
 }
}
