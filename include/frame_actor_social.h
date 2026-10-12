#ifndef FRAME_ACTOR_SOCIAL_H
#define FRAME_ACTOR_SOCIAL_H
struct FrameObject;
struct FramePoint;
struct FrameActorNeedState;
/* Selector-specific overlay; countdown and cue phases are inferred roles. */
struct FrameActorSocialWork {
 unsigned char unknown_00[0x58]; int timer;
 unsigned short cue_count,cue_timer;
};
extern unsigned char g_frame_actor_social_probe[];
int frame_read_signed_parameter(const void *,unsigned int);
unsigned char frame_actor_need_value(struct FrameActorNeedState *,unsigned int);
void resource_set_triple(unsigned int,unsigned int,unsigned int);
struct FrameActorTerrainState { unsigned char unknown_00[0x85]; unsigned char terrain; };
unsigned char frame_map_terrain_at(struct FramePoint);
#endif
