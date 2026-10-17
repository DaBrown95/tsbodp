#include "frame_actor_attachment_job_25.h"
unsigned int frame_begin_attachment_job_25(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind) {
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record(owner,actor);
 struct FramePoint point;unsigned char result;
 if(!job)result=0;
 else {
 job->kind=kind;frame_attachment_position(owner->object,1,&point);
 frame_begin_actor_route(actor,&point,&job->status,0,1);
 frame_request_animation((struct FrameCommandObject *)actor,6);result=1;
 }
 return result;
}
