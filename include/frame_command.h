#include "frame_tick.h"
struct FrameCommandObject {
 struct FrameObject *next;
 FrameU32 unknown_04;
 FrameU16 id, subtype;
 FrameU32 flags;
 FrameU8 unknown_10[61];
 FrameU8 state, variant_state, pending_updates;
 FrameU8 unknown_50[179];
 signed char requested_animation;
};
void frame_request_actor_animation(struct FrameCommandObject *, FrameU8);
void frame_stop_motion(struct FrameObject *);
void frame_request_animation(struct FrameCommandObject *, FrameU8);
void frame_set_variant_state(struct FrameObject *, FrameU8);
FrameU8 frame_find_objects(FrameU8, FrameU8, struct FrameObject **, FrameU8);
