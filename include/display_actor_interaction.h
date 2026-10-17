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
struct FrameActorAttachmentRecord *frame_allocate_actor_attachment_record(struct FrameNeedEffectState *,struct FrameObject *);
struct FrameActorAttachmentRecord *frame_find_actor_attachment_record(struct FrameNeedEffectState *,struct FrameObject *);
unsigned char frame_release_actor_attachment_record(struct FrameNeedEffectState *,struct FrameObject *);
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
/* Remaining observed row57 callbacks; action49 uses the legacy _31 family. */
unsigned int frame_interaction_initialize_31(struct FrameNeedEffectState *);
unsigned int frame_interaction_select_31(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_interaction_prepare_31(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
void frame_interaction_finish_31(struct FrameNeedEffectState *);

/* Native route-begin adapter names remain provisional. */
unsigned int frame_begin_route_attachment_12b54(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);
unsigned int frame_begin_route_attachment_259a0(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);
unsigned int frame_begin_route_attachment_43884(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);
unsigned int frame_begin_route_attachment_46240(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_job_68(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);

#endif
