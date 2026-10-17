#include "frame_need_effect.h"
#include "frame_actor_state.h"
#include "frame_actor_attachment.h"
static inline struct FrameActorAttachmentRecord *attachment_record(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 unsigned char i;
 for(i=0;i<3;i++) {
  if(owner->records[i].actor==actor)return &owner->records[i];
 }
 return 0;
}
unsigned int frame_actor_attachment_status(struct FrameObject *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *record=attachment_record((struct FrameNeedEffectState *)owner,actor);
 unsigned int result;
 if(record->status==2){record->running=0;result=1;}
 else if(record->status==3){record->running=0;frame_finish_actor_attachment(record);result=2;}
 else if(record->status==1){frame_cancel_actor_route(record->actor);result=1;}
 else result=((struct FrameNeedEffectState *)owner)->step((struct FrameNeedEffectState *)owner,actor);
 if(result==2 || result==0) {
  struct FrameActorAttachmentRecord *finished=attachment_record((struct FrameNeedEffectState *)owner,record->actor);
  if(finished){finished->actor=0;finished->timer=94;}
 }
 return result;
}
asm(".align 2, 0");
