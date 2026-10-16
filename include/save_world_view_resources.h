#ifndef SAVE_WORLD_VIEW_RESOURCES_H
#define SAVE_WORLD_VIEW_RESOURCES_H

struct BackgroundResource;

/* A selection is a four-byte-aligned character-representation window.
 * Bytes 0..3 supply the masked word; byte 4 is read only for the third
 * segment. The interface does not establish an enclosing allocation size
 * or a resource-table capacity. */
/* Isolate the base typedef before applying the old frontend's type attribute. */
typedef unsigned char SceneViewResourceSelectionByteBase;
typedef SceneViewResourceSelectionByteBase SceneViewResourceSelectionByte
    __attribute__((aligned(4)));
extern const struct BackgroundResource * const *g_scene_view_resource_groups[];
/* Separate address views of an observed eight-byte placement record. */
extern unsigned int g_scene_view_resource_background;
extern unsigned short g_scene_view_resource_tile, g_scene_view_resource_palette;
extern const struct BackgroundResource g_scene_view_fixed_resource;
void scene_view_load_selected_resource(unsigned int, int, int, unsigned int,
    unsigned int, const SceneViewResourceSelectionByte *);
void scene_view_load_fixed_resource(unsigned int, unsigned int, unsigned int);

#endif
