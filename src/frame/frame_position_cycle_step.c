#include "frame_position_cycle_jobs.h"
unsigned int frame_position_cycle_step(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 struct FrameActorNeedState *needs=((struct FrameActorObject *)job->actor)->actor_state;
 switch ((unsigned int)job->timer) {
 case 0:
  ((struct FrameActorObject *)job->actor)->direction=((struct FrameActorObject *)owner->object)->direction;
  if (((struct FrameActorObject *)owner->object)->direction==3||((struct FrameActorObject *)owner->object)->direction==5)
   frame_need_effect_handoff_bounds(job->actor,owner,1);
  frame_attachment_position(owner->object,3,&job->actor->position);
  job->timer=41;
  frame_request_animation((struct FrameCommandObject *)job->actor,50);
  ((struct FrameActorStateWork *)job->actor)->timer=90;
  break;
 case 41:
  if (job->actor->flags&0x400000) {
   unsigned int attachment=g_frame_interaction_settings.attachment_mode!=1;
   frame_attachment_position(owner->object,attachment,&job->actor->position);
   job->timer=42;
   audio_play_animation_cue(65);
   frame_request_animation((struct FrameCommandObject *)job->actor,52);
   ((struct FrameActorStateWork *)job->actor)->timer=90;
   frame_commit_need_effect(owner->object,1);
  }
  break;
 case 42:
  if (job->actor->flags&0x400000) {
   frame_clear_animation_pending(job->actor);
   job->timer=43;
  }
  break;
 case 43:
  frame_adjust_actor_needs(needs,22,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
  if (!(unsigned char)frame_step_attachment_need_timer(job,needs,4,&((struct FrameActorStateWork *)job->actor)->timer)) {
   job->timer=1;
   frame_request_animation((struct FrameCommandObject *)job->actor,6);
   frame_commit_need_effect(owner->object,0);
   frame_begin_actor_route(job->actor,&((struct FrameAttachmentSavedPosition *)owner)->position,&job->status,4,1);
  }
  break;
 case 1:
  ((struct FrameActorObject *)job->actor)->before_step=resource_object_before_step;
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  return 2;
 }
 return 1;
}
asm(".align 2, 0");
