#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_speed_exit.h"
void frame_speed_exit_tick(struct FrameObject *object)
{
 frame_update_actor_state(object);
 if(((struct FrameActorObject *)object)->state==4)frame_speed_exit_transition(object);
}
asm(".align 2, 0");
