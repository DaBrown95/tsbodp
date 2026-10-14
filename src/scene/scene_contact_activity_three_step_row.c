#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
#define OBJECT ((struct SceneContactActivityThreeObject*)base)
#define EVENT ((struct SceneContactActivityThreeObject*)STATE->event)
#define CONTROL g_scene_contact_activity_three_control
static inline void observer_absolute_point(struct FramePoint *point) {
 frame_read_attachment((struct FrameObject*)STATE->observer.address,0,point);
 point->x=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.x+((unsigned int)point->x<<16));
 point->y=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.y+((unsigned int)point->y<<16));
}
void scene_contact_activity_three_step_row(struct FrameObject *base) {
 unsigned int direction=OBJECT->direction;
 struct FramePoint target;
 int speed;struct SceneContactActivityThreeState *state;
 switch(OBJECT->outcome) {
 case 1:
  if(STATE->event&&(unsigned char)(EVENT->outcome-3)<=1) {
   if(EVENT->phase) {OBJECT->outcome=9;--STATE->active_rows;}
   else if(CONTROL.selection.word==OBJECT->palette_source&&view_point_distance(OBJECT->position,STATE->event->position)<=0x3fffff)OBJECT->outcome=3;
  }
  break;
 case 2:
  if(--OBJECT->timer==0xffffffff) {OBJECT->outcome=4;OBJECT->direction=32;}
  observer_absolute_point(&target);
  direction=scene_contact_activity_three_direction_to_point(OBJECT->position.x,OBJECT->position.y,target.x,target.y);
  speed=(int)(0u-(unsigned int)EVENT->speed);
  scene_contact_activity_three_advance_vector(base,speed,direction);
    {
     struct FrameObject *event=STATE->event;
     OBJECT->position=OBJECT->next_position;
     event->position=OBJECT->next_position;
    }
    scene_contact_activity_three_original_update_linked_row(base);
  break;
 case 3:
  state=STATE;
  if(state->event&&!((struct SceneContactActivityThreeObject*)state->event)->phase) {
   direction=scene_contact_activity_three_direction_to_point(EVENT->position.x,EVENT->position.y,OBJECT->position.x,OBJECT->position.y);
   scene_contact_activity_three_advance_vector(base,4*65536,direction);
   if(view_point_distance(OBJECT->next_position,STATE->event->position)<=0x3ffff) {
    OBJECT->palette_source=0;OBJECT->outcome=11;EVENT->outcome=11;OBJECT->direction=32;
    EVENT->phase=1;STATE->event->flags&=~1u;
    if(OBJECT->subtype==4)audio_select_sequence(29);else audio_select_sequence(35);
    audio_play_animation_cue(196);
   }
   OBJECT->position=OBJECT->next_position;
   break;
  }else goto unavailable_event;
  break;
 case 4:
  state=STATE;
  if(state->event) {
   if(g_input_pressed[0]&128) {
    if((g_input_pressed[0]&1)&&frame_random_range(1,100)>g_scene_contact_activity_three_row_definitions[OBJECT->subtype].escape_threshold-OBJECT->amount) {
     OBJECT->outcome=9;--STATE->active_rows;EVENT->outcome=3;STATE->event->flags|=1;
     scene_contact_activity_three_original_mark_selection(CONTROL.selection.word);
     audio_play_animation_cue(192);audio_select_sequence(28);
    }else {OBJECT->outcome=11;EVENT->outcome=11;OBJECT->direction=32;}
   }else {
    observer_absolute_point(&target);
    direction=scene_contact_activity_three_direction_to_point(OBJECT->position.x,OBJECT->position.y,target.x,target.y);
    speed=(int)((unsigned int)g_scene_contact_activity_three_row_definitions[OBJECT->subtype].speed+((unsigned int)OBJECT->phase<<13));
    speed=(int)((unsigned int)speed-(unsigned int)EVENT->speed);
    scene_contact_activity_three_advance_vector(base,speed,direction);
    {
     struct FrameObject *event=STATE->event;
     OBJECT->position=OBJECT->next_position;
     event->position=OBJECT->next_position;
    }
    scene_contact_activity_three_original_update_linked_row(base);
   }
  }else {
unavailable_event:
   OBJECT->outcome=9;--state->active_rows;
  }
  break;
 case 5:OBJECT->flags|=2;break;
 case 9:
  observer_absolute_point(&target);
  direction=scene_contact_activity_three_direction_to_point(OBJECT->position.x,OBJECT->position.y,target.x,target.y);
  scene_contact_activity_three_advance_vector(base,6*65536,direction);
  if(OBJECT->next_position.x<0||OBJECT->next_position.y<0||OBJECT->next_position.x>240*65536||OBJECT->next_position.y>160*65536)OBJECT->outcome=5;
  OBJECT->position=OBJECT->next_position;
  break;
 case 11:
  if(OBJECT->flags&0x400000) {
   OBJECT->timer=20;OBJECT->outcome=2;EVENT->outcome=4;OBJECT->direction=32;
   ((struct FrameObject*)STATE->observer.address)->flags&=~16u;
   frame_set_animation_frame((struct FrameTickObject*)STATE->observer.address,0);
   if(OBJECT->phase<=1)audio_play_animation_cue(193);
   else if(OBJECT->phase<=4)audio_play_animation_cue(194);
   else audio_play_animation_cue(195);
  }
  break;
 case 6:case 7:case 8:case 10:break;
 }
 if(direction!=OBJECT->direction) {OBJECT->direction=direction;scene_contact_activity_three_reset_row(base);}
}
asm(".align 2,0");
