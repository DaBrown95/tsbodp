#include "scene_palette_menu_selection_transition.h"

static inline unsigned int selection_row_count(unsigned int row)
{
    const unsigned char *entries = g_scene_palette_menu_owner->parameters;
    entries += 2;
    entries += row;
    return *entries;
}

void scene_palette_menu_build_selection_objects(void)
{
    unsigned int row, column;
    /* Target-word carrier for the returned object address and indexed store. */
    unsigned int object;

    g_scene_palette_menu_owner->initial_word = 25;
    for (row = 0; row <= 4; ++row) {
        column = 0;
        for (; column < selection_row_count(row); ++column) {
            struct ScenePaletteMenuOwner *owner;
            object = (unsigned int)
                scene_palette_menu_create_selection_object(column,
                    106 + column * 3, 46 + row * 20);
            owner = g_scene_palette_menu_owner;
            owner->groups[row][column] = (struct FrameObject *)object;
            --owner->initial_word;
        }
    }
    for (column = 0; column < g_scene_palette_menu_owner->initial_word;
        ++column) {
        struct ScenePaletteMenuOwner *owner;
        object = (unsigned int)
            scene_palette_menu_create_selection_object(column,
                83 + column * 3, 28);
        owner = g_scene_palette_menu_owner;
        owner->available[column] = (struct FrameObject *)object;
    }
}
asm(".align 2, 0");
