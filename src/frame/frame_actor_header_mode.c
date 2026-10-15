#include "frame_need_effect_header_jobs.h"
#include "display_actor_interaction.h"
unsigned char frame_actor_header_mode(struct FrameObject *actor)
{
 if(!actor->id)return g_frame_interaction_settings.attachment_mode;
 return g_frame_actor_definitions[actor->unknown_0a-32][0];
}
