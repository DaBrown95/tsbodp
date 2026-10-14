#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
#define CONTROL g_scene_contact_activity_three_control
void scene_contact_activity_three_step(void) {
 unsigned int value=0;
 if(STATE->flags&1)return;
 if(STATE->restore_sequence) {
  if(--STATE->sound_timer==65535) {
   audio_select_sequence(28);STATE->restore_sequence=value;
  }
 }
 switch(CONTROL.phase) {
 case 0:
  if(g_input_pressed[0]&1) {
   value=scene_contact_activity_three_get_value(CONTROL.selection.word);
   if(!value)return;
   CONTROL.phase=1;STATE->primary->flags|=16;
   scene_contact_activity_three_refresh_value(CONTROL.selection.bytes[0],CONTROL.selection.bytes[0]);
   audio_play_animation_cue(197);
  } else if(g_input_pressed[0]&192) {
   value=CONTROL.selection.word;
   CONTROL.selection.word=input_step_vertical_pressed(&CONTROL.selection.word,0,2,1,0);
   {
    register unsigned int selected asm("r4")=(unsigned char)value;
    scene_contact_activity_three_refresh_value(selected,(unsigned char)CONTROL.selection.word);
   }
   scene_contact_activity_three_refresh_value(CONTROL.selection.bytes[0],CONTROL.selection.bytes[0]);
   frame_set_position(STATE->cursor,8*65536,112*65536+(CONTROL.selection.word<<20));
   audio_play_animation_cue(197);
  }
  break;
 case 1:
  if(g_input_pressed[0]&1) {
   STATE->primary->flags&=~16u;STATE->secondary->flags|=16;CONTROL.phase=2;
   audio_play_animation_cue(197);
  }
  break;
 case 2:
  if(g_input_pressed[0]&1) {
   STATE->secondary->flags&=~16u;
   STATE->event=scene_contact_activity_three_create_event();CONTROL.phase=3;
   STATE->primary->flags&=~1u;STATE->observer.object->flags|=1;
   STATE->sound_handle=audio_play_animation_cue(190);
  }
  break;
 case 3:
  if(STATE->flags&2) {
   if(!CONTROL.refresh_count)for(value=0;value<=4;++value)scene_contact_activity_three_create_row(value);
   else CONTROL.refresh_count=0;
   CONTROL.phase=4;CONTROL.timer=30;
   frame_set_animation_program(STATE->primary,(struct FrameSpriteResource*)&g_scene_contact_activity_three_primary_animation,g_scene_contact_activity_three_primary_commands,0);
   frame_set_animation_program(STATE->secondary,(struct FrameSpriteResource*)&g_scene_contact_activity_three_secondary_animation,g_scene_contact_activity_three_secondary_commands,0);
   STATE->primary->flags|=1;STATE->observer.object->flags&=~1u;STATE->flags&=~2u;
  }
  break;
 case 4:
  if(--CONTROL.timer==0xffffffff)CONTROL.phase=0;
  break;
 }
}
asm(".align 2,0");
