#include "frame_actor_attachment_parameters.h"
void frame_set_attachment_parameter_indicator(struct FrameObject *object,unsigned char percentage)
{
 unsigned char divisor=100/(((struct FrameActorObject *)object)->resource->sequence->frame_count-1);
 unsigned char frame=frame_indicator_unsigned_divide(percentage,divisor);
 if(frame!=((struct FrameActorObject *)object)->previous_frame)frame_set_animation_frame((struct FrameTickObject *)object,frame);
}
asm(".align 2, 0");
