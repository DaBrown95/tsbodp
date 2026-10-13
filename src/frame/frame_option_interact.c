#include "frame_option_object.h"

static inline unsigned int frame_option_allowed(unsigned short value) { return value<=1; }
static inline unsigned int frame_option_pressed(unsigned char value) { register unsigned int key asm("r2")=1; key&=value; return key; }
void frame_option_interact(struct FrameObject *base,struct FrameObject *other)
{
 struct FrameOptionObject *object=(struct FrameOptionObject *)base;
 struct FrameOptionObject *actor=(struct FrameOptionObject *)other;
 struct FrameObject *player;
 unsigned char facing;
 unsigned int is_player,allowed;
 register unsigned int key asm("r2");
 if(object->state==18 || actor->state!=16) return;
 player=((struct FrameOptionPlayerContext *)&g_input_config)->players[g_input_config.local_player].object;
 facing=frame_scene_effect_facing_available(other,base);
 is_player=actor->id==0;
 key=frame_option_pressed((unsigned char)g_input_pressed[((struct FrameOptionInputSlot *)player)->input_slot]);
 allowed=frame_option_allowed((unsigned short)(object->subtype-1));
 if(allowed && is_player && key && facing) {
  frame_stop_motion((struct FrameObject *)object);
  transition_object_set_state((struct TransitionObject *)object,18);
  frame_set_variant_state((struct FrameObject *)object,0);
  transition_object_set_state((struct TransitionObject *)actor,0);
  object->target=(struct FrameObject *)actor;
  input_clear();
 }
}
asm(".align 2, 0");
