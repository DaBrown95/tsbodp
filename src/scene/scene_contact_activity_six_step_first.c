#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_step_first(struct FrameObject *base) {
 if(!STATE->first && !((struct FrameActorObject *)base)->actor_id && (unsigned int)base->position.y-24u*65536 <=48u*65536-1)
  STATE->first=base;
 if(STATE->first==base && base->position.y<24*65536)STATE->first=0;
 scene_contact_activity_six_remove_finished(base);
}
asm(".align 2,0");
