#ifndef FRAME_ACTOR_FINISH_H
#define FRAME_ACTOR_FINISH_H
/* Bounded spatial word view; complete allocation and units are provisional. */
struct FrameActorFinishBounds {
 unsigned char unknown00[0x98]; void (*before_step)(struct FrameObject *);
 struct FramePoint lower,upper;
};
struct FrameObject *frame_create_actor(unsigned int,unsigned char,int,int);
#endif
