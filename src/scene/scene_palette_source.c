#include "scene_palette.h"
#include "frame_map_scene.h"

void *scene_palette_source(void)
{
    void *palette;
    const unsigned int *scene;
    switch (g_scene_context.period) {
    default:
    no_palette:
        scene = &g_scene_id;
        goto fallback;
    case 0:
        if (g_scene_context.flags & 1) {
            unsigned int table_address = (unsigned int)g_scene_period_palettes;
            const unsigned int *index = &g_scene_id;
            unsigned int offset = *index * sizeof(struct ScenePeriodPalette);
            table_address += 12;
            palette = *(void *const *)(offset + table_address);
            scene = index;
        } else {
            unsigned int table_address = (unsigned int)g_scene_period_palettes;
            const unsigned int *index = &g_scene_id;
            unsigned int offset = *index * sizeof(struct ScenePeriodPalette);
            palette = *(void *const *)(offset + table_address);
            scene = index;
        }
        break;
    case 1:
        if (!(g_scene_context.flags & 1))
            goto no_palette;
        {
            unsigned int table_address = (unsigned int)g_scene_period_palettes;
            const unsigned int *index = &g_scene_id;
            unsigned int offset = *index * sizeof(struct ScenePeriodPalette);
            table_address += 12;
            palette = *(void *const *)(offset + table_address);
            scene = index;
        }
        break;
    case 2:
        {
            unsigned int table_address = (unsigned int)g_scene_period_palettes;
            const unsigned int *index = &g_scene_id;
            unsigned int offset = *index * sizeof(struct ScenePeriodPalette);
            table_address += 4;
            palette = *(void *const *)(offset + table_address);
            scene = index;
        }
        break;
    case 3:
        {
            unsigned int table_address = (unsigned int)g_scene_period_palettes;
            const unsigned int *index = &g_scene_id;
            unsigned int offset = *index * sizeof(struct ScenePeriodPalette);
            table_address += 8;
            palette = *(void *const *)(offset + table_address);
            scene = index;
        }
        break;
    }
    if (palette)
        return palette;
 fallback:
    return (void *)g_frame_map_scene_resources[*scene].unknown40;
}
