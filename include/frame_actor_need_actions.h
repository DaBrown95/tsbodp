#ifndef FRAME_ACTOR_NEED_ACTIONS_H
#define FRAME_ACTOR_NEED_ACTIONS_H

#include "frame_actor_needs.h"
#include "audio_game.h"

/* Serialized 24-byte records; animation callers consume the low byte. */
struct FrameActorNeedAction {
 FrameU8 variant_state, unknown_01[3];
 FrameU32 animation;
 int indicator;
 FrameU16 frames;
 FrameU8 unknown_0e[2];
 FrameU32 cue_nonzero_variant, cue_zero_variant;
};
extern struct FrameActorNeedAction g_frame_actor_need_actions[8];
FrameU8 frame_need_action_forbidden(FrameU32);
struct FrameObject *frame_spawn_need_effect(int, int, int, int, int);
FrameU8 frame_configure_need_effect(struct FrameObject *, int, int, int);
void frame_commit_need_effect(struct FrameObject *, FrameU8);
unsigned char frame_actor_choose_walk_direction(struct FrameObject *);
void frame_actor_choose_need_action(struct FrameActorNeedState *, struct FrameActorObject *);

#endif
