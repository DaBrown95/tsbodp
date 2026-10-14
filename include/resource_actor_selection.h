#ifndef RESOURCE_ACTOR_SELECTION_H
#define RESOURCE_ACTOR_SELECTION_H

#include "display_menu_relation.h"

/* Two overlapping access views. Neither describes the complete game state. */
struct ResourceSelectionWorld {
    unsigned char unknown00[0x440];
    unsigned int stage;
    unsigned char unknown444[0x747 - 0x444];
    unsigned char requested;
};
struct ResourceSelectionRelationView {
    struct DisplayMenuRelationValues values;
    unsigned char unknown68[0x717 - 0x68];
    unsigned char selection_requested;
};
extern struct ResourceSelectionWorld g_resource_selection_world;
extern struct ResourceSelectionRelationView g_resource_selection_relation_view;

unsigned char resource_select_actor(unsigned int, unsigned int);
unsigned char resource_actor_selection_available(unsigned int, unsigned int);

/* The count provider reads the existing context collection at game +31C. */
extern unsigned char g_scene_entry_data[];
int resource_count_selectable_actor_entries(void);

/* Explicit original dependencies; their names and roles remain provisional. */
unsigned char resource_selection_has_kind_0804573c(void);
void resource_selection_remove_080454dc(void);
void resource_selection_group_ids_08045794(int *);
unsigned int resource_selection_kind_available_0804565c(unsigned int);

#endif
