#ifndef DISPLAY_ACTOR_INTERACTION_H
#define DISPLAY_ACTOR_INTERACTION_H
#include "frame_need_effect.h"
#include "frame_actor_state.h"
#include "frame_actor_attachment.h"
struct FrameActorNeedState;
struct FrameCommandObject;
/* Game-state byte +20 selects attachment mode; other bytes are unspecified. */
struct FrameInteractionSettings { unsigned char unknown00[32],attachment_mode; };
extern struct FrameInteractionSettings g_frame_interaction_settings;
unsigned char frame_attachment_position(struct FrameObject *,unsigned char,struct FramePoint *);
void frame_request_animation(struct FrameCommandObject *,unsigned char);
void frame_commit_need_effect(struct FrameObject *,unsigned int);
void frame_adjust_actor_needs(struct FrameActorNeedState *,unsigned int,unsigned char);
struct FrameActorAttachmentRecord *frame_allocate_actor_attachment_record(struct FrameActorAttachmentOwner *,struct FrameObject *);
struct FrameActorAttachmentRecord *frame_find_actor_attachment_record(struct FrameActorAttachmentOwner *,struct FrameObject *);
unsigned char frame_release_actor_attachment_record(struct FrameActorAttachmentOwner *,struct FrameObject *);
/* The step caller observes only the low byte of the timer result. */
unsigned int frame_step_attachment_need_timer(struct FrameActorAttachmentRecord *,struct FrameActorNeedState *,unsigned int,int *);
unsigned int frame_interaction_step_31(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_interaction_dispatch_31(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_interaction_begin_31(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned char frame_interaction_can_begin_31(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int audio_play_animation_cue(unsigned int);
unsigned char frame_actor_need_value(struct FrameActorNeedState *,unsigned int);
unsigned char frame_actor_need_average(struct FrameActorNeedState *);
unsigned char frame_attachment_need_is_low(struct FrameActorNeedState *,unsigned int);
#endif
