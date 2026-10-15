#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
#define OBJECT ((struct SceneContactActivityThreeObject*)base)
#define EVENT ((struct SceneContactActivityThreeObject*)STATE->event)
static inline void linked_observer_point(struct FramePoint *point) {
 frame_read_attachment((struct FrameObject*)STATE->observer.address,0,point);
 point->x=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.x+((unsigned int)point->x<<16));
 point->y=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.y+((unsigned int)point->y<<16));
}
void scene_contact_activity_three_update_linked_row(struct FrameObject *base) {
 struct FramePoint target;
 linked_observer_point(&target);
 if(OBJECT->next_position.y<(int)((unsigned int)target.y-5u*65536)||OBJECT->next_position.y>(int)((unsigned int)target.y+5u*65536)) {
  if(OBJECT->next_position.x>=0&&OBJECT->next_position.y>=0&&OBJECT->next_position.x<=240*65536&&OBJECT->next_position.y<=160*65536)return;
 }
 OBJECT->outcome=5;EVENT->outcome=5;STATE->event=0;--STATE->active_rows;
 if(OBJECT->next_position.y>=(int)((unsigned int)target.y-5u*65536)&&OBJECT->next_position.y<=(int)((unsigned int)target.y+5u*65536)) {
  display_load_background(1,g_scene_contact_activity_three_row_definitions[OBJECT->subtype].background,STATE->completed*6+1,(unsigned short)(15-STATE->completed),STATE->completed*4,1);
  { int base_score;scene_contact_add_activity_score((base_score=20+OBJECT->subtype*5)+OBJECT->amount*(OBJECT->subtype+2)); }
  ++STATE->completed;if(STATE->completed>4)STATE->flags|=1;
  audio_select_sequence((unsigned char)g_scene_contact_activity_three_row_definitions[OBJECT->subtype].sequence);
  STATE->sound_timer=g_scene_contact_activity_three_row_definitions[OBJECT->subtype].sound_timer;STATE->restore_sequence=1;
 }else audio_select_sequence(28);
 scene_contact_activity_three_decrement_value(g_scene_contact_activity_three_control.selection.word);
}
asm(".align 2,0");
