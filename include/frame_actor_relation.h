#ifndef FRAME_ACTOR_RELATION_H
#define FRAME_ACTOR_RELATION_H

/* Partial ROM descriptor: 44-byte stride, text IDs +00, background +0C, cue +20, variant +25. */
struct BackgroundResource;
struct FrameActorGreetingDescriptor {
 const unsigned short *text_ids;
 unsigned char unknown_04[8];
 const struct BackgroundResource *background_resource;
 unsigned char unknown_10[16];
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
