#include "scene_contact_menu.h"

static inline const void *map_field(const void *base, unsigned int offset)
{
    unsigned int address = (unsigned int)base;
    address += offset;
    return *(const void *const *)address;
}

void scene_contact_load_primary_resources(unsigned int index)
{
    const union SceneContactMapResources *resources = g_scene_contact_map_resources;
    unsigned int offset = index * sizeof(union SceneContactMapResources);
    const void *extra_types;

#define FIELD(name) map_field(&resources->fields.name, offset)
    resource_decode_alternate(FIELD(tiles0), (void *)0x06000000);
    resource_decode_alternate(FIELD(tiles1), (void *)0x06008000);
    frame_set_map_sources(&g_scene_contact_initial_background_control1,
                         &g_scene_contact_activity_background_control1);
    display_load_palette(FIELD(palette), 0, 256);
    frame_load_map_resources(0, FIELD(map0), FIELD(secondary0));
    frame_load_map_resources(1, FIELD(map1), FIELD(secondary1));
    frame_load_combined_map_resource(0, FIELD(combined0), FIELD(combined0_second));
    frame_load_combined_map_resource(1, FIELD(combined1), FIELD(combined1_second));
    frame_decode_map_cell_types(FIELD(cell_data), FIELD(cell_types));
    extra_types = FIELD(extra_cell_types);
    if (extra_types)
        frame_decode_extra_map_cell_types(FIELD(extra_cell_data), extra_types);
    frame_reset_object_palette_slots();
#undef FIELD
}
