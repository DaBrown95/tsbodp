#ifndef FRAME_PLACEMENT_SESSION_H
#define FRAME_PLACEMENT_SESSION_H
#include "frame_need_effect_registration.h"
#include "frame_actor_grid.h"
#include "frame_placement.h"
#include "view_configuration.h"
struct FramePlacementSession {
 void *grid;
 struct FrameObject *effect,*actor,*preview;
 struct FramePoint original_position;
 struct FrameActorPackedCell selected,original_cell;
 unsigned char original_direction;
};
struct FramePlacementActor { unsigned char unknown00[0x68],mode; };
extern struct FramePlacementSession g_frame_placement_session;
extern unsigned char g_frame_interaction_directions[];
extern unsigned char g_frame_placement_rotations[][2];
extern signed char g_frame_placement_steps[][2];
extern struct FrameSpriteResource *g_frame_placement_resources[];
extern unsigned char g_frame_placement_commands[];
/* Two-word configuration access view already used by scene actor setup. */
extern unsigned int g_transition_view_configuration[2];
void transition_set_view_origin(struct FramePoint,unsigned char);
void frame_disable_primary_object_flags(unsigned int);
unsigned char frame_grid_cell_corner(void *,const int *,struct FramePoint *);
#endif
