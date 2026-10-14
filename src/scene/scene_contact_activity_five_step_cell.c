#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_step_cell(struct FrameObject *base)
{
 struct SceneContactActivityFiveObject *object=(struct SceneContactActivityFiveObject *)base;
 switch(object->phase) {
 case 0:break;
 case 4:
  if (--object->timer==0) {
   struct SceneContactActivityFiveState *state;
   unsigned int secondary,reward;
   frame_set_animation_program((struct FrameObject *)object,(struct FrameSpriteResource *)(g_scene_contact_activity_five_cell_animations+(object->subtype<<4)),g_scene_contact_activity_five_cell_program+8,0);
   object->phase=1;
   object->timer=4;
   state=STATE;
   reward=g_scene_contact_activity_five_rows[state->option].combo_reward;
   secondary=(unsigned short)state->combo_count;
   state->score+=reward*secondary;
   state->combo_count=secondary+1;
  }
  break;
 case 1:
  if (--object->timer==0) object->flags=(object->flags&~1)|0x82;
  break;
 case 14:
  {
   int x=object->position.x,target_x=object->destination.x;
   int y=object->position.y,target_y=object->destination.y;
   if (x==target_x && y==target_y) {
    audio_play_animation_cue(215);
    object->phase=0;
   } else {
    if (object->velocity.x>0x80000) object->acceleration.x=0;
    if (x>target_x) {
     object->position.x=target_x;
     object->velocity.x=0;
     object->acceleration.x=0;
    }
    if (object->velocity.y>0x80000) object->acceleration.y=0;
    if (y>target_y) {
     object->position.y=target_y;
     object->velocity.y=0;
     object->acceleration.y=0;
    }
   }
  }
  break;
 }
}
asm(".align 2,0");
