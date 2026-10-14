#include "input.h"
#include "frame_contact_action.h"

void frame_begin_contact_action(struct CollisionObject *owner,struct CollisionObject *other) {
 struct ContactActionView *object=(struct ContactActionView *)owner;
 struct ContactActionView *partner=(struct ContactActionView *)other;
 if(partner->id==0 && object->state==0 && partner->state==16 && (g_input_pressed[0]&1)) {
  partner->state=0;
  object->state=4;
  object->partner=(struct FrameObject *)other;
  input_clear();
 }
}
asm(".align 2,0");
