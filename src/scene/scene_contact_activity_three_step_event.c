#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
#define CONTROL g_scene_contact_activity_three_control
static inline void observer_absolute_point(struct FramePoint *point) {
 frame_read_attachment((struct FrameObject*)STATE->observer.address,0,point);
 point->x=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.x+((unsigned int)point->x<<16));
 point->y=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.y+((unsigned int)point->y<<16));
}
void scene_contact_activity_three_step_event(struct FrameObject *base) {
 struct SceneContactActivityThreeObject *object=(void*)base;
 switch(object->outcome) {
 case 0:
 {
  int next_x,next_y;
  object->speed=(int)((unsigned int)object->speed-19660u);
  scene_contact_activity_three_advance_vector((struct FrameObject*)object,object->speed,object->direction);
  if(object->speed<=0||(next_y=object->next_position.y)<0||(next_x=object->next_position.x)<0||next_x>240*65536) {
   object->speed=0;object->outcome=3;object->flags|=16;
   audio_play_animation_cue(191);audio_game_stop_sample(STATE->sound_handle);
  }else {object->position.x=next_x;object->position.y=next_y;}
 }
  break;
 case 3:
  if(g_input_current[0]&1) {
   struct FramePoint target;
   observer_absolute_point(&target);
   object->direction=scene_contact_activity_three_direction_to_point(target.x,target.y,object->position.x,object->position.y);
   scene_contact_activity_three_advance_vector((struct FrameObject*)object,5*65536,object->direction);
   if(object->next_position.y>=(int)((unsigned int)target.y-5u*65536)&&object->next_position.y<=(int)((unsigned int)target.y+5u*65536)) {
    object->outcome=5;STATE->event=0;
   }else {object->position.x=object->next_position.x;object->position.y=object->next_position.y;}
  }
  break;
 case 4:
  if(g_input_pressed[0]&1)object->speed=5*65536;else object->speed=0;
  break;
 case 5:
  object->flags|=2;STATE->event=0;
  scene_contact_activity_three_remove_slots();STATE->flags|=2;
  if(!object->phase&&(short)STATE->active_rows)CONTROL.refresh_count=1;
  break;
 case 1:case 2:case 6:case 7:case 8:case 9:case 10:case 11:break;
 }
 if(!(object->flags&2))scene_contact_activity_three_original_draw_event((struct FrameObject*)object);
}
asm(".align 2,0");
