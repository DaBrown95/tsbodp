#include "display_catalog_text.h"
void display_catalog_draw_details(unsigned int layer, int x, int y, int width,
                                  unsigned int item, int index, unsigned int style)
{
    const char *text = 0;
    struct DisplayCatalogType *types = g_display_catalog_state.context->types;
    if (item == 0x52 && index != -1) {
        switch (types[index].type) {
            case 0: text = display_scene_lookup_text(0x37a); break;
            case 1: text = display_scene_lookup_text(0x381); break;
            case 2: text = display_scene_lookup_text(0x37b); break;
            case 3: text = display_scene_lookup_text(0x384); break;
            case 4: text = display_scene_lookup_text(0x37e); break;
            case 5: text = display_scene_lookup_text(0x37c); break;
            case 6: text = display_scene_lookup_text(0x37f); break;
            case 7: text = display_scene_lookup_text(0x385); break;
            case 8: text = display_scene_lookup_text(0x380); break;
            case 9: text = display_scene_lookup_text(0x382); break;
            case 10: text = display_scene_lookup_text(0x383); break;
            case 11: text = display_scene_lookup_text(0x37d); break;
        }
    } else if (item == 0x20 && index != -1) {
        switch (types[index].type) {
            case 0: text = display_scene_lookup_text(0x338); break;
            case 1: text = display_scene_lookup_text(0x33f); break;
            case 2: text = display_scene_lookup_text(0x339); break;
            case 3: text = display_scene_lookup_text(0x342); break;
            case 4: text = display_scene_lookup_text(0x33c); break;
            case 5: text = display_scene_lookup_text(0x33b); break;
            case 6: text = display_scene_lookup_text(0x33d); break;
            case 7: text = display_scene_lookup_text(0x343); break;
            case 8: text = display_scene_lookup_text(0x33e); break;
            case 9: text = display_scene_lookup_text(0x341); break;
            case 10: text = display_scene_lookup_text(0x340); break;
            case 11: text = display_scene_lookup_text(0x33a); break;
        }
    } else text = display_scene_lookup_text(g_display_scene_catalog[item].unknown_04);
    display_text_draw_all_lines(layer, x, y, width, text, style);
}
