#include "heap.h"
#include "frame_scene_actor_schedule.h"
void frame_actor_note_remove(unsigned int id)
{
 if(id>17)g_frame_scene_actor_presence[id-18]=0;
}
asm(".align 2,0");
