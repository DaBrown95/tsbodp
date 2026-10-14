#include "input.h"
#include "scene_contact_activity_two_access.h"
#define STATE ((struct SceneContactActivityTwoState *)g_scene_contact_state)
void scene_contact_activity_two_step(void) {
 struct SceneContactActivityTwoState *state=STATE;
 if(state->score==0) {STATE->flags|=1;return;}
 if(!(STATE->flags&2)) {
  struct FrameObject *first=state->primary;
  if((first->flags&16)&&(g_input_pressed[0]&1)) {
   { struct SceneContactActivityTwoControlWord flags=scene_contact_activity_two_read_control(first);
   flags.bits &= ~16u;
   scene_contact_activity_two_write_control(first,flags); }
   { struct SceneContactActivityTwoControlWord flags=scene_contact_activity_two_read_control(state->secondary);
   flags.bits |= 17u;
   scene_contact_activity_two_write_control(state->secondary,flags); }
  } else if((STATE->secondary->flags&16)&&(g_input_pressed[0]&1)) {
   struct SceneContactActivityTwoState *other=STATE;
   { struct SceneContactActivityTwoControlWord flags=scene_contact_activity_two_read_control(other->primary);
   flags.bits &= ~1u;
   scene_contact_activity_two_write_control(other->primary,flags); }
   { struct SceneContactActivityTwoControlWord flags=scene_contact_activity_two_read_control(other->secondary);
   flags.bits &= ~16u;
   scene_contact_activity_two_write_control(other->secondary,flags); }
   scene_contact_activity_two_begin_transfer(other->secondary->shared_slot,other->primary->shared_slot);
   STATE->flags|=2;
  }
 }
}
asm(".align 2, 0");
