#ifndef FRAME_GRID_CELLS_H
#define FRAME_GRID_CELLS_H

#include "frame_actor_target_cells.h"
struct FrameObject;

/* Cells expose the low two packed axis bytes; masks arrive as complete words. */
void frame_grid_add_occupancy(void *, const void *, unsigned int);
void frame_grid_remove_occupancy(void *, const void *, unsigned int);
void frame_grid_clear_occupancy(void *, const void *);
void frame_grid_add_terrain(void *, const void *, unsigned int);
void frame_grid_remove_terrain(void *, const void *, unsigned int);
void frame_grid_clear_terrain(void *, const void *);
void frame_destroy_map_registration(void *);
unsigned char frame_probe_need_effect_position(void *, struct FrameObject *, int, int);

#endif
