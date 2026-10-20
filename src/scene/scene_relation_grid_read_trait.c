#include "scene_relation_grid.h"

unsigned int scene_relation_grid_read_trait(const void *state, unsigned int index)
{
    const unsigned char *traits = (const unsigned char *)state + 2;
    return traits[index];
}
