#ifndef FRAME_ACTOR_RELATION_H
#define FRAME_ACTOR_RELATION_H

/* Partial ROM descriptor: 44-byte stride, cue record +20, variant +25. */
struct FrameActorGreetingDescriptor {
 unsigned char unknown_00[32];
 const unsigned int *cue_record;
 unsigned char unknown_24, cue_variant, unknown_26[6];
};
extern struct FrameActorGreetingDescriptor g_frame_actor_greetings[];

/* State 46 reads a signed byte at game-state +39 + 4*(actor_id-18). */
struct FrameActorRelation {
 unsigned char unknown_00;
 signed char value;
 unsigned char unknown_02[2];
};
struct FrameActorRelationState {
 unsigned char unknown_00[0x38];
 struct FrameActorRelation records[1];
};

#endif
