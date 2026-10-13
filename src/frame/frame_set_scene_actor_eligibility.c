#include "heap.h"
#include "frame_scene_actor_schedule.h"
void frame_set_scene_actor_eligibility(unsigned char enabled)
{
 g_frame_scene_actor_eligibility_enabled=enabled;
}
asm(".align 2,0");
