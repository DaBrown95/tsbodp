#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_attachment.h"
unsigned char frame_count_actor_attachments(struct FrameObject *object)
{
 unsigned char count=0;
 struct FrameObject **slot=((struct FrameActorAttachmentView *)object)->slots;
 int i;
 for(i=1;i>=0;slot++,i--)if(*slot)count++;
 return count;
}
asm(".align 2, 0");
