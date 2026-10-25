#ifndef DISPLAY_CONDITION_PANEL_H
#define DISPLAY_CONDITION_PANEL_H

#include "display_scene_lifecycle.h"
#include "display_text_fields.h"
#include "frame_actor_scene.h"
#include "resource_conditions.h"

/* Access views of the existing world and UI-slot storage, not complete states. */
struct ConditionPanelCell {
    unsigned char first, second, unknown02[22];
};
struct ConditionPanelWorld {
    unsigned int unknown00;
    int number;
    unsigned char unknown08[0x438];
    unsigned int row;
    struct ConditionPanelCell cells[1][6];
};
struct ConditionPanelLabelCoordinate {
    unsigned char x, y, unknown02[2];
};
extern struct ConditionPanelWorld g_condition_panel_world;
extern struct FrameObject *g_condition_panel_objects[15];
extern const struct ConditionPanelLabelCoordinate g_condition_panel_label_coordinates[5];

void condition_panel_create_objects(void);
void condition_panel_draw_row_labels(unsigned int);
void condition_panel_update_column_objects(unsigned int);

/* Existing byte-consuming provider; the object pointer remains a FrameObject. */
void frame_set_variant_state(struct FrameObject *, unsigned char);

#endif
