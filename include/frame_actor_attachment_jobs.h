#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_H

#include "display_actor_interaction.h"
#include "display_need_effect_lifecycle.h"
#include "frame_actor_target_jobs.h"
#include "frame_actor_actions.h"
#include "audio_game.h"
#include "frame_random.h"

/* A 32-byte ROM row. The animation word is narrowed by the animation API.
 * Names describe observed controller reads, rather than a complete format. */
struct FrameAttachmentRouteVariant {
    unsigned int kind;
    unsigned int animation;
    unsigned int initial_code, timer_need, adjustment_need, parameter;
    unsigned char cue;
    signed char attachment;
    unsigned char wait_animation, restore_bounds, stop_sample, unknown1d[3];
};
extern struct FrameAttachmentRouteVariant g_frame_attachment_route_variants[];
struct FrameAttachmentSavedPosition {
    unsigned char unknown00[0x64];
    struct FramePoint position;
};
/* The chance producer consumes two bytes per row, with no four-byte padding. */
struct FrameAttachmentChance {
    unsigned char chance, parameter;
} __attribute__((packed));
extern struct FrameAttachmentChance g_frame_attachment_chances[];
/* Only this storage's first word is interpreted as an actor pointer. */
extern struct FrameObject *g_need_effect_player;
unsigned char frame_gate_attachment_game_value(struct FrameNeedEffectState *,
                                                struct FrameActorAttachmentRecord *, int);
unsigned int frame_begin_variant_attachment_job(struct FrameNeedEffectState *,
                                                   struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_job_73(struct FrameNeedEffectState *,
                                            struct FrameObject *, unsigned int);
unsigned int frame_step_attachment_job_73(struct FrameNeedEffectState *,
                                           struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_attachment_job_73(struct FrameNeedEffectState *,
                                               struct FrameObject *);
/* Actual observed rows35/36 definition callbacks for kind73. */
unsigned int frame_initialize_attachment_job_73(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_73(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_attachment_job_73(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
void frame_finish_attachment_job_73(struct FrameNeedEffectState *);

/* Separate neighbouring entries; no installed callback role is established. */
unsigned int frame_check_attachment_job_73(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_job_73_default_value(void);

#endif
