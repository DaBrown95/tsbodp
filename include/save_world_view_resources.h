#ifndef SAVE_WORLD_VIEW_RESOURCES_H
#define SAVE_WORLD_VIEW_RESOURCES_H

struct BackgroundResource;

/* The masked word read covers bytes zero through three; byte four selects the
 * third palette segment. This access view does not establish a full object size. */
struct SceneViewResourceSelection {
    union {
        unsigned int word;
        struct {
            unsigned char group, first, variant, second;
        } fields;
    } prefix;
    unsigned char third;
};

extern const struct BackgroundResource * const *g_scene_view_resource_groups[];
/* Separate address views of an observed eight-byte placement record. */
extern unsigned int g_scene_view_resource_background;
extern unsigned short g_scene_view_resource_tile, g_scene_view_resource_palette;
extern const struct BackgroundResource g_scene_view_fixed_resource;
void scene_view_load_selected_resource(unsigned int, int, int, unsigned int,
    unsigned int, const struct SceneViewResourceSelection *);
void scene_view_load_fixed_resource(unsigned int, unsigned int, unsigned int);

#endif
