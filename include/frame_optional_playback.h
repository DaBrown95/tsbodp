#ifndef FRAME_OPTIONAL_PLAYBACK_H
#define FRAME_OPTIONAL_PLAYBACK_H

#include "frame_optional_choice_context.h"

/* Bounded state overlay. The existing parameter halfword at +0x70 is read
 * signed by these callbacks; completed is the byte at +0x64. */
struct FrameOptionalPlaybackState {
    unsigned char unknown_00[0x64];
    unsigned char completed, unknown_65[11];
    short parameter;
    unsigned char optional;
};
struct FrameOptionalPlaybackActorTimer {
    unsigned char unknown_00[0x58];
    int timer;
};
extern const unsigned short g_optional_playback_cues_256[];
extern const unsigned short g_optional_playback_cues_other[];

unsigned int frame_initialize_optional_playback_context(struct FrameNeedEffectState *);
/* No incoming reference is established for this adjoining availability API. */
unsigned int frame_optional_playback_context_available(struct FrameNeedEffectState *,
                                                        struct FrameObject *);
unsigned int frame_select_optional_playback_attachment_kind(struct FrameNeedEffectState *,
                                                            unsigned char *);
/* Original eight-byte constant-return provider; its LR preservation remains
 * unconverted, and no redundant source operations are inserted to mimic it. */
unsigned int frame_check_optional_playback_attachment_kind(struct FrameNeedEffectState *,
                                                           struct FrameObject *, unsigned int);
unsigned int frame_begin_optional_playback_attachment_job(struct FrameNeedEffectState *,
                                                          struct FrameObject *, unsigned int);
unsigned int frame_dispatch_optional_playback_attachment_job(struct FrameNeedEffectState *,
                                                             struct FrameObject *);
void frame_optional_playback_publish_completion(struct FrameNeedEffectState *);
void frame_optional_playback_play_cue(struct FrameNeedEffectState *);
void frame_optional_playback_select_sequence(struct FrameNeedEffectState *);
unsigned int frame_step_optional_playback_job_45(struct FrameNeedEffectState *,
                                                 struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_playback_job_1_6(struct FrameNeedEffectState *,
                                                  struct FrameActorAttachmentRecord *, unsigned int);
unsigned int frame_step_optional_playback_job_56_57(struct FrameNeedEffectState *,
                                                    struct FrameActorAttachmentRecord *, unsigned int);
unsigned int frame_step_optional_playback_job_62(struct FrameNeedEffectState *,
                                                 struct FrameActorAttachmentRecord *);

unsigned char frame_begin_actor_route(struct FrameObject *, struct FramePoint *,
                                      unsigned int *, unsigned int, unsigned char);
void frame_commit_need_effect(struct FrameObject *, unsigned int);

#endif
