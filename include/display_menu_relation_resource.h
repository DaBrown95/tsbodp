#ifndef DISPLAY_MENU_RELATION_RESOURCE_H
#define DISPLAY_MENU_RELATION_RESOURCE_H
#include "display_menu_relation.h"

struct BackgroundResource;
/* Getter-view base; this path observes values/flags at +8 onward. */
extern struct DisplayMenuRelationValues g_display_menu_relation_values;
extern const struct BackgroundResource g_display_menu_relation_resource8;
extern const struct BackgroundResource g_display_menu_relation_resource4;
extern const struct BackgroundResource g_display_menu_relation_resource1;
extern const struct BackgroundResource g_display_menu_relation_resource2;
extern const struct BackgroundResource *g_display_menu_relation_resources[];
void display_menu_load_relation_resource(void);
void display_menu_restore_footer(void);

#endif
