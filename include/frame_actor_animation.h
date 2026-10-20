#ifndef FRAME_ACTOR_ANIMATION_H
#define FRAME_ACTOR_ANIMATION_H
#include "frame_command.h"
struct FrameVariantResource {
 FrameU8 *pixels;
 struct FrameSpriteSequence *sequence;
 FrameU16 *palette;
 FrameU8 frame_delay, unknown_0d[3];
};
struct FrameActorAnimation {
 struct FrameVariantResource *variants;
 FrameU8 *commands;
};
extern struct FrameActorAnimation g_frame_actor_animation_sets[][7];
extern FrameU8 g_frame_actor_special_event;
extern FrameU32 g_frame_world_id;
extern FrameU8 g_frame_actor_direction_variants[];
void frame_set_animation_record(struct FrameObject *, struct FrameVariantResource *);

#endif
