#include "frame_map_scene.h"

/* Independently bounded getter; callers and unused formals unknown. */
unsigned short frame_unrooted_read_extra_map_cell_2b2c8(unsigned short x,
                                                      unsigned short y)
{
    struct FramePoint dimensions;
    unsigned char **cell_types_owner;
    int byte_offset;

    frame_get_map_dimensions(&dimensions);
    cell_types_owner = &g_frame_map_extra_cell_types;
    byte_offset = ((x >> 5) + (y >> 5) * (dimensions.x >> 5)) * 2;
    return *(unsigned short *)(*cell_types_owner + byte_offset);
}
