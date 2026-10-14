#include "input.h"
#include "frame_scene_trigger.h"
void frame_scene_trigger_contact(struct CollisionObject *owner,struct CollisionObject *other) {
 struct SceneTriggerView *object=(struct SceneTriggerView *)owner;
 struct SceneTriggerView *partner=(struct SceneTriggerView *)other;
 if(partner->id==0 && partner->state==16 && (g_input_pressed[partner->player]&1)) {
  resource_submit_scene(21,0,object->selector);
  input_clear();
 }
}
asm(".align 2,0");
