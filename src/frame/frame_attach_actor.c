#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_attachment.h"
static inline void frame_attachment_set_outer_state(struct FrameObject *object,unsigned char state){if(((struct FrameActorObject *)object)->state!=state){((struct FrameActorObject *)object)->state=state;((struct FrameActorObject *)object)->pending_updates|=1;}}
unsigned char frame_attach_actor(struct FrameObject *object,struct FrameObject *target)
{
 int i=0;
 for(;i<2;i++) {
  unsigned int index=i*4;
  unsigned int base=(unsigned int)object+0x138;
  struct FrameObject **slot=(struct FrameObject **)(base+index);
  if(!*slot) {
   *slot=target;
   frame_attachment_set_outer_state(object,17);
   return 1;
  }
 }
 return 0;
}
asm(".align 2, 0");
