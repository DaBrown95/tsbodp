#include "frame_actor_attachment_parameters.h"
void frame_attachment_parameter_indicator_tick(struct FrameObject *object)
{
 switch(((struct FrameActorObject *)object)->state) {
 case 0:break;
 case 1:object->flags|=2;break;
 }
}
