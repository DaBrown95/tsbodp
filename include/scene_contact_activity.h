#ifndef SCENE_CONTACT_ACTIVITY_H
#define SCENE_CONTACT_ACTIVITY_H

#include "view_effects.h"

/* Specific effect-only calls through the contact definition table. This does
 * not refine other callback interfaces or recover unconverted callee types. */
typedef void (*SceneContactActivityCallback)(void);

struct TransitionViewObject;
struct SceneContactActivityStatePrefix {
    struct TransitionViewObject *view;
    unsigned int unknown04;
};
union SceneContactMapResources {
    struct {
        const void *map0, *combined0, *combined0_second, *secondary0;
        const void *map1, *combined1, *combined1_second, *secondary1;
        const void *cell_data, *cell_types, *extra_cell_data, *extra_cell_types;
        const void *tiles0, *tiles1, *palette;
    } fields;
    unsigned int words[15];
};
extern const union SceneContactMapResources g_scene_contact_map_resources[];
extern const unsigned int g_scene_contact_initial_background_control1;
extern const unsigned int g_scene_contact_activity_background_control1;

void scene_contact_initialize_primary_activity(void);
void scene_contact_initialize_secondary_activity(void);
void scene_contact_step_primary_activity(void);
void scene_contact_step_secondary_activity(void);
void scene_contact_load_primary_resources(unsigned int);

/* Existing providers for the connected activity path. */
void scene_vblank_callback(void);
void transition_reset_view(unsigned char);
void transition_step_view(unsigned char);
void frame_update_map_view(unsigned char);
void frame_step_transient_effects(void);
void frame_set_map_sources(const void *, const void *);
void frame_load_map_resources(unsigned int, const void *, const void *);
void frame_load_combined_map_resource(unsigned int, const void *, const void *);
void frame_decode_map_cell_types(const void *, const void *);
void frame_decode_extra_map_cell_types(const void *, const void *);
void frame_reset_object_palette_slots(void);

#endif
