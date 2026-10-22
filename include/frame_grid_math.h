#ifndef FRAME_GRID_MATH_H
#define FRAME_GRID_MATH_H

#include "frame_map_scene.h"
#include "frame_actor_grid.h"
#include "frame_actor_state.h"

/* Low bytes of a packed cell hold its two grid axes; upper bytes stay unspecified. */
unsigned char frame_grid_coordinates_to_point(struct FrameMapRegistration *, const struct FramePoint *, struct FramePoint *);
/* Provisional status API for the original inverse projection; points may alias. */
unsigned char resource_project_point(void *, const struct FramePoint *, struct FramePoint *);
unsigned char frame_grid_snap_point_to_center(void *, const struct FramePoint *, struct FramePoint *);
unsigned char frame_grid_snap_point_to_corner(void *, const struct FramePoint *, struct FramePoint *);
unsigned char frame_grid_cell_corner(void *, const int *, struct FramePoint *);
unsigned char frame_grid_cell_extents(void *, const int *, struct FramePoint *, struct FramePoint *);

static inline unsigned char frame_grid_project_coordinates(struct FrameMapRegistration *registration, const struct FramePoint *coordinates, struct FramePoint *point)
{
 if(coordinates->x<0 || coordinates->x>=(int)registration->span || coordinates->y<0 || coordinates->y>=(int)registration->span)
  return 0;
 point->x=registration->origin_x+coordinates->x+coordinates->y;
 point->y=registration->origin_y-coordinates->x/2+coordinates->y/2+8;
 return 1;
}

#endif
