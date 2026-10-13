#ifndef DISPLAY_CATALOG_TEXT_H
#define DISPLAY_CATALOG_TEXT_H
#include "display_text_draw.h"
#include "display_text_resource.h"
/* Partial catalog/state views inferred from observed word and byte accesses. */
struct DisplayCatalogItem {
    unsigned int id, unknown_04, text_id, category, unknown_10, description;
};
struct DisplayCatalogType {
    unsigned char unknown_00[2], type, unknown_03;
};
struct DisplayCatalogContext {
    unsigned int unknown_00;
    struct DisplayCatalogType *types;
};
struct DisplayCatalogState {
    unsigned char unknown_00[240];
    struct DisplayCatalogContext *context;
};
extern struct DisplayCatalogState g_display_catalog_state;
extern const struct DisplayCatalogItem g_display_scene_catalog[];
extern char *g_display_text_buffer;
extern const char *display_scene_lookup_text(unsigned int);
extern int display_text_measure_width(const char *);
extern int display_catalog_draw_name(unsigned int, int, int,
                                     unsigned int, int, unsigned int);
extern void display_catalog_draw_details(unsigned int, int, int, int,
                                         unsigned int, int, unsigned int);
#endif
