#include "scene_palette_menu_selection_transition.h"

static inline unsigned int selection_row_count(unsigned int row,
    unsigned int field_offset)
{
    const unsigned char *entries = *(const void **)
        ((unsigned int)g_scene_palette_menu_owner + field_offset);
    entries += 2;
    entries += row;
    return *entries;
}

void scene_palette_menu_release_selection_objects(void)
{
    unsigned int row = 0, column;
    unsigned int field_offset =
        (unsigned int)&((struct ScenePaletteMenuOwner *)0)->parameters;

    do {
        for (column = 0; column < selection_row_count(row, field_offset);
            ++column) {
            g_scene_palette_menu_owner->groups[row][column]->flags |= 2;
            g_scene_palette_menu_owner->groups[row][column] = 0;
        }
        ++row;
    } while (row <= 4);

    for (column = 0; column < g_scene_palette_menu_owner->initial_word;
        ++column) {
        g_scene_palette_menu_owner->available[column]->flags |= 2;
        g_scene_palette_menu_owner->available[column] = 0;
    }
}

asm(".align 2,0");
