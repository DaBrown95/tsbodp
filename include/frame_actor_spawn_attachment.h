#ifndef FRAME_ACTOR_SPAWN_ATTACHMENT_H
#define FRAME_ACTOR_SPAWN_ATTACHMENT_H

#include "frame_need_effect_optional_state.h"
#include "frame_actor_finish.h"

/* Observed row50 selects action87; existing job87 names denote row87. */
unsigned int frame_initialize_actor_spawn_attachment(struct FrameNeedEffectState *);
unsigned int frame_select_actor_spawn_attachment(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_actor_spawn_attachment(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_actor_spawn_attachment(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_actor_spawn_attachment(struct FrameNeedEffectState *, struct FrameObject *);
void frame_tick_actor_spawn_attachment(struct FrameNeedEffectState *);
unsigned int frame_step_actor_spawn_attachment(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);

/* Separate neighbouring entry; no installed callback role is established. */
unsigned int frame_check_actor_spawn_attachment(struct FrameNeedEffectState *, struct FrameObject *);

#endif
