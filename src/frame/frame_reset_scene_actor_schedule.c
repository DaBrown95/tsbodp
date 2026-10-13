#include "heap.h"
#include "frame_scene_actor_schedule.h"
void frame_reset_scene_actor_schedule(void)
{
 heap_clear(g_frame_scene_actor_presence,0,24);
 g_frame_scene_actor_schedule_timer=300;
 g_frame_scene_actor_eligibility_enabled=1;
}
asm(".align 2,0");
