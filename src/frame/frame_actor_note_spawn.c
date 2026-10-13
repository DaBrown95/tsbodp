#include "heap.h"
#include "frame_scene_actor_schedule.h"
void frame_actor_note_spawn(unsigned int id)
{
 if(id>17)g_frame_scene_actor_presence[id-18]=1;
}
asm(".align 2,0");
