#include "frame_actor_needs.h"
int frame_actor_need_delta(struct FrameActorNeedState *state, unsigned int i, struct FrameObject *object)
{
 int *rates;
 if (!object->id) rates = g_frame_actor_need_delta_player;
 if (object->id) rates = g_frame_actor_need_delta_npc;
 return rates[i];
}
