#include "frame_actor_group.h"

struct FrameSpriteVariant **frame_read_actor_group_part2_variants(
    const void *data)
{
    const unsigned char *definition = data;
    return g_actor_group_part2_tables[definition[0]];
}
