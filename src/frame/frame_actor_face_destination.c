#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
unsigned char frame_actor_face_destination(struct FrameObject *object)
{
 unsigned int done=0;
 unsigned char direction=frame_direction_to_destination(object->position,object->destination,((struct FrameActorObject *)object)->speed);
 if(direction==8){direction=((struct FrameActorObject *)object)->direction;done=1;}
 frame_set_actor_direction(object,direction);
 return done;
}
