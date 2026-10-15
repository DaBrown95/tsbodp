#ifndef FRAME_ACTOR_PALETTE_SCENE_H
#define FRAME_ACTOR_PALETTE_SCENE_H

#include "frame_actor_group.h"

/* Access views for the existing scene-selection word and signed positions. */
struct FrameActorPaletteSceneSelection {
    unsigned char unknown_00[12];
    unsigned int index;
};
#include "frame_actor_palette_scene_points.h"
/* Eight selectors begin at a saved record's +0x20; rows retain its 40-byte
 * stride. The following bytes overlap later record/state fields. */
struct FrameActorPaletteSceneRow {
    unsigned char selectors[8], unknown_08[32];
};

extern const unsigned char *g_frame_actor_palette_scene_resource;
extern struct FrameActorPaletteSceneSelection g_frame_actor_palette_scene_selection;
extern struct FrameObject *g_frame_actor_palette_scene_object;
extern struct FrameActorPaletteSceneRow g_frame_actor_palette_scene_rows[];
extern struct FrameSpriteVariant **g_frame_actor_palette_scene_part0[];
extern struct FrameSpriteVariant ***g_frame_actor_palette_scene_part1[];

void frame_create_palette_scene_actor(unsigned int);

#endif
