#ifndef FRAME_LAYER_H
#define FRAME_LAYER_H

#include "frame.h"

/* Map pointers and coordinate roles inferred from the layer lookup accesses. */
extern unsigned short *g_frame_layer_blocks;
extern unsigned char *g_frame_layer_cells;
void frame_get_map_dimensions(struct FramePoint *);
unsigned int frame_layer_at_position(unsigned int, unsigned int);

#endif
