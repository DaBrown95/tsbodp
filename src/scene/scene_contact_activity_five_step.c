#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_step(void)
{
 unsigned int found=0;
 scene_contact_activity_five_refresh();
 switch(g_scene_request.unknown_10) {
 case 0:
  scene_contact_activity_five_update_selection();
  if(g_input_pressed[0]&1) {
   scene_contact_activity_five_reset_selection();
   scene_contact_activity_five_set_selection(STATE->selected_column,STATE->selected_row);
   if(STATE->selected_count) {
    scene_contact_activity_five_remove_marked_cells();
    g_scene_request.unknown_10=1;
    audio_play_animation_cue(211);
   } else audio_play_animation_cue(3);
  }
  break;
 case 1:
  if(scene_contact_activity_five_selection_finished())g_scene_request.unknown_10=2;
  break;
 case 2:
  if(scene_contact_activity_five_advance()) {
   if(scene_contact_activity_five_has_adjacent_pair()==1) {
    int i,random;
    scene_contact_activity_five_clamp_selection();
    for(i=8-STATE->column_count;i<8;++i) {
     if(STATE->column_heights[i]<=6) {found=1;break;}
    }
    random=frame_random_range(1,100);
    if(found&&random<g_scene_contact_activity_five_rows[STATE->option].chance) {
     g_scene_request.unknown_10=3;
     scene_contact_activity_five_create_followup();
     STATE->flags|=2;
    }else g_scene_request.unknown_10=0;
   }else {
    g_scene_request.unknown_10=4;
    g_scene_request.unknown_14=15;
    scene_contact_activity_five_begin_end();
   }
   scene_contact_add_activity_score(STATE->score);
   STATE->score=0;
   STATE->combo_count=0;
  }
  break;
 case 3:
  found=(unsigned char)(STATE->flags&2);
  if(!found) {
   if(scene_contact_activity_five_has_adjacent_pair()==1)g_scene_request.unknown_10=found;
   else {
    g_scene_request.unknown_10=4;
    g_scene_request.unknown_14=15;
    scene_contact_activity_five_begin_end();
   }
  }
  break;
 case 4:
  if(--g_scene_request.unknown_14==(unsigned int)-1)STATE->flags|=1;
  break;
 }
}
asm(".align 2, 0");
