#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_actions.h"
int frame_add_game_value(int amount)
{
 int value=((struct FrameActorValueWorld *)&g_resource_game_state)->value+amount;
 struct FrameActorValueWorld *state;
 unsigned int address,offset;
 int maximum;
 ((struct FrameActorValueWorld *)&g_resource_game_state)->value=value;
 maximum=999999;
 state=(struct FrameActorValueWorld *)&g_resource_game_state;
 if(value>maximum) state->value=maximum;
 else if(value<0) state->value=0;
 address=(unsigned int)&g_scene_mode_flags;
 offset=g_frame_actor_need_input.local_player*56;
 address+=4;
 *(unsigned int *)(offset+address)|=2;
 return state->value;
}
