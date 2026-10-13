#ifndef FRAME_ACTOR_ATTACHMENT_PARAMETERS_H
#define FRAME_ACTOR_ATTACHMENT_PARAMETERS_H

#include "frame_actor_attachment_jobs.h"
#include "frame_actor_effect.h"
#include "frame_transient_effect.h"
#include "input.h"

/* Bounded controller views; unrelated storage retains its original bytes. */
struct FrameAttachmentJobWork {
    unsigned char unknown00[0x58];
    struct FrameObject *indicator;
    unsigned short unknown5c;
    unsigned char variant, unknown5f[5];
    struct FramePoint saved_position;
    unsigned char unknown6c[0x74];
    unsigned int sample;
};
struct FrameAttachmentPhaseClock {
    unsigned char unknown00[0x5e];
    unsigned short counter;
};
struct FrameAttachmentUiFlags {
    unsigned int unknown00, flags;
    unsigned char unknown08[48];
};
extern unsigned char g_frame_actor_social_probe[];
extern struct FrameVariantResource g_attachment_indicator_resources[];
extern int g_attachment_indicator_palettes[];
extern unsigned int g_attachment_parameter_rates[][10];
extern struct FrameAttachmentUiFlags g_attachment_parameter_ui[];

unsigned int frame_step_variant_attachment_job(struct FrameNeedEffectState *,
                                                struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_variant_attachment_job(struct FrameNeedEffectState *,
                                                    struct FrameObject *);
void frame_clear_attachment_need_countdown(struct FrameActorNeedState *);
void frame_need_effect_handoff_bounds(struct FrameObject *, struct FrameNeedEffectState *,
                                      unsigned char);
struct FrameObject *frame_create_attachment_parameter_indicator(struct FrameObject *,
                                                                unsigned int);
void frame_complete_attachment_parameter_indicator(struct FrameObject *);
void frame_set_attachment_parameter_indicator(struct FrameObject *, unsigned char);
void frame_attachment_parameter_indicator_tick(struct FrameObject *);
unsigned int frame_read_parameter_percentage(const void *, unsigned int);
void frame_update_attachment_parameter(void *, unsigned int, struct FrameObject *);
/* The original unsigned division backend is distinct from signed __divsi3. */
unsigned int frame_indicator_unsigned_divide(unsigned int, unsigned int);
void frame_set_animation_frame(struct FrameTickObject *, unsigned char);

#endif
