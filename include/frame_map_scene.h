#ifndef FRAME_MAP_SCENE_H
#define FRAME_MAP_SCENE_H

#include "frame_map.h"
#include "scene.h"

/* Partial serialized 72-byte records inferred from the scene/map load path. */
struct FrameMapTileResource;
struct FrameMapBackgroundControl;
struct FrameMapSceneResource {
 const void *selection0, *selection1, *primary0, *combined0, *combined0_alternate, *secondary0;
 const void *primary1, *combined1, *combined1_alternate, *secondary1;
 const void *cell_data, *cell_types, *extra_cell_data, *extra_cell_types, *registration_data;
 const struct FrameMapTileResource *tile_resource;
 unsigned int unknown40;
 unsigned char deferred_layer, unknown45[3];
};
extern const struct FrameMapSceneResource g_frame_map_scene_resources[];

/* This 20-byte view is initialized by the original grid helper at 0x48B78. */
struct FrameMapRegistration {
 void *data;
 int origin_x, origin_y;
 unsigned int span;
 unsigned short extent;
 unsigned char cell_size, unknown13;
};
unsigned char frame_initialize_map_registration(struct FrameMapRegistration *, unsigned short, unsigned short, unsigned char);
void *frame_create_map_registration(unsigned short, unsigned short, unsigned char);
void frame_configure_deferred_display(unsigned char);
void frame_load_scene_map_resources(unsigned int);
void frame_load_selected_map_tiles(const struct FrameMapTileResource *, const void *, const struct FrameMapBackgroundControl *);
void frame_initialize_map_cell_buffers(void);
void frame_decode_map_cell_types(const void *, const void *);
void frame_decode_extra_map_cell_types(const void *, const void *);
extern unsigned char *g_frame_map_cell_data, *g_frame_map_cell_types;
extern unsigned char *g_frame_map_extra_cell_types, *g_frame_map_extra_decode;
extern unsigned int g_frame_map_cell_data_bytes, g_frame_map_cell_count, g_frame_map_cell_header;

/* Palette state shares its base with the existing partial users-byte view. */
struct FrameMapPaletteSlot {
 unsigned char id, unknown01, users, unknown03;
 const void *const *sources;
};
struct FrameMapPaletteState {
 unsigned int frame;
 struct FrameMapPaletteSlot slots[16];
};
extern struct FrameMapPaletteState g_frame_map_palette_state;
extern const void *g_frame_map_palette_resources[];
void frame_define_palette_slot(unsigned int, const void *const *);
void frame_initialize_map_palette_slots(void);

struct FrameMapDma { const void *source; void *destination; unsigned int control; };
#define FRAME_MAP_DMA3 ((volatile struct FrameMapDma *)0x040000D4)

#endif
