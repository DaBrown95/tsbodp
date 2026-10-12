#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

unsigned char frame_actor_choose_walk_direction(struct FrameObject *object)
{
 int cell, next, second;
 int initial, first, fallback, direction;
 unsigned int next_flags, second_flags, next_occupied, second_occupied;
 first=fallback=-1;
 cell=((struct FrameActorGridCell *)object)->cell;
 direction=frame_random_range(1,7);
 initial=g_actor_wander_directions[direction];
 direction=initial;
 frame_grid_neighbor(g_frame_registration,&cell,&next,direction);
 frame_grid_neighbor(g_frame_registration,&next,&second,direction);
 do {
  next_flags=frame_grid_terrain(g_frame_registration,&next);
  second_flags=frame_grid_terrain(g_frame_registration,&second);
  next_occupied=frame_grid_occupancy(g_frame_registration,&next);
  second_occupied=frame_grid_occupancy(g_frame_registration,&second);
  if ((next_flags&2) && (second_flags&2) && !(next_occupied&0x3d) && !(second_occupied&0x3d)) {
   first=direction;
   if (frame_actor_direction_available(object,direction)==1) {
    frame_set_actor_direction(object,direction);
    return 1;
   }
  }
  direction+=2;
  if (direction>8) direction-=8;
  frame_grid_neighbor(g_frame_registration,&cell,&next,direction);
  frame_grid_neighbor(g_frame_registration,&next,&second,direction);
 } while (direction!=initial);
 do {
  next_flags=frame_grid_terrain(g_frame_registration,&next);
  next_occupied=frame_grid_occupancy(g_frame_registration,&next);
  if ((next_flags&2) && !(next_occupied&0x3d)) {
   fallback=direction;
   if (frame_actor_direction_available(object,direction)==1) {
    frame_set_actor_direction(object,direction);
    return 1;
   }
  }
  direction+=2;
  if (direction>8) direction-=8;
  frame_grid_neighbor(g_frame_registration,&cell,&next,direction);
 } while (direction!=initial);
 if (first!=-1)
  frame_set_actor_direction(object,first);
 else if (fallback!=first)
  frame_set_actor_direction(object,fallback);
 return 0;
}
asm(".align 2, 0");
