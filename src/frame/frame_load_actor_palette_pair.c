#include "frame_actor_group.h"

void frame_load_actor_palette_pair(void)
{
    frame_load_actor_group_palette(g_frame_actor_palette_pair_definition, 1);
    frame_load_actor_group_alternate_palette(g_frame_actor_palette_pair_definition, 2);
}

asm(".align 2, 0");
