#ifndef FRAME_ACTOR_NEED_INPUT_H
#define FRAME_ACTOR_NEED_INPUT_H

struct FrameObject;
struct FrameActorNeedInput {
 struct {
  struct FrameObject *actor;
  unsigned short flags;
  unsigned char unknown_06[6];
 } views[4];
 unsigned char player_count, local_player;
};
extern struct FrameActorNeedInput g_frame_actor_need_input;

#endif
