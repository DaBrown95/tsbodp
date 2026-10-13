#include "frame_scene_player.h"
#include "frame_actor_state.h"
#include "input.h"
struct FrameScenePlayerInput {unsigned char unknown00[19],input_slot;};
unsigned char frame_scene_effect_facing_available(struct FrameObject *,struct FrameObject *);
void frame_scene_effect_interact(struct FrameObject *base,struct FrameObject *other_base) {
 struct FrameActorObject *object=(struct FrameActorObject *)base;
 struct FrameActorObject *other=(struct FrameActorObject *)other_base;
 struct FrameObject *player;
 unsigned char available;
 int primary;
 unsigned char pressed;
 if(object->state==29 && object->variant_state!=52 && object->variant_state!=30 && other->state==16) {
  player=g_frame_scene_player_slots[((const struct InputConfig *)g_frame_scene_player_slots)->local_player].object;
  available=frame_scene_effect_facing_available((struct FrameObject *)other,(struct FrameObject *)object);
  primary=other->id==0;
  pressed=g_input_pressed[((struct FrameScenePlayerInput *)player)->input_slot]&1;
  if(primary && pressed && available) {
   frame_set_actor_direction((struct FrameObject *)object,frame_direction_toward((struct FrameObject *)object,(struct FrameObject *)other));
   frame_set_actor_direction((struct FrameObject *)other,frame_direction_toward((struct FrameObject *)other,(struct FrameObject *)object));
   frame_set_variant_state((struct FrameObject *)other,2);
   frame_stop_motion((struct FrameObject *)object);
   transition_object_set_state((struct FrameObject *)object,30);
   frame_set_variant_state((struct FrameObject *)object,0);
   ((struct FrameSceneSavedEffect *)object)->partner=(struct FrameObject *)other;
   g_input_pressed[((struct FrameScenePlayerInput *)player)->input_slot]&=0xfffe;
  }
 }
}
