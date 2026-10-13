#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_attachment.h"
void frame_detach_actor(struct FrameObject *object,struct FrameObject *target)
{
 int i=0;
 struct FrameObject *empty=0;
 struct FrameObject **slot=((struct FrameActorAttachmentView *)object)->slots;
 do {
  if(*slot==target){*slot=empty;break;}
  slot++;i++;
 }while(i<=1);
}
