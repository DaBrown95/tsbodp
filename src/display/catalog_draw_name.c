#include "display_catalog_text.h"
int display_catalog_draw_name(unsigned int layer, int x, int y,
                              unsigned int item, int index, unsigned int style)
{
    const char *text = 0;
    struct DisplayCatalogType *types = g_display_catalog_state.context->types;
    if (item == 0x52 && index != -1) {
        switch (types[index].type) {
            case 0: text = display_scene_lookup_text(0x257); break;
            case 1: text = display_scene_lookup_text(0x25e); break;
            case 2: text = display_scene_lookup_text(0x258); break;
            case 3: text = display_scene_lookup_text(0x261); break;
            case 4: text = display_scene_lookup_text(0x25b); break;
            case 5: text = display_scene_lookup_text(0x259); break;
            case 6: text = display_scene_lookup_text(0x25c); break;
            case 7: text = display_scene_lookup_text(0x262); break;
            case 8: text = display_scene_lookup_text(0x25d); break;
            case 9: text = display_scene_lookup_text(0x25f); break;
            case 10: text = display_scene_lookup_text(0x260); break;
            case 11: text = display_scene_lookup_text(0x25a); break;
        }
    } else if (item == 0x20 && index != -1) {
        switch (types[index].type) {
            case 0: text = display_scene_lookup_text(0x215); break;
            case 1: text = display_scene_lookup_text(0x21c); break;
            case 2: text = display_scene_lookup_text(0x216); break;
            case 3: text = display_scene_lookup_text(0x21f); break;
            case 4: text = display_scene_lookup_text(0x219); break;
            case 5: text = display_scene_lookup_text(0x218); break;
            case 6: text = display_scene_lookup_text(0x21a); break;
            case 7: text = display_scene_lookup_text(0x220); break;
            case 8: text = display_scene_lookup_text(0x21b); break;
            case 9: text = display_scene_lookup_text(0x21e); break;
            case 10: text = display_scene_lookup_text(0x21d); break;
            case 11: text = display_scene_lookup_text(0x217); break;
        }
    } else text = display_scene_lookup_text(g_display_scene_catalog[item].text_id);
    display_scene_stage_0801a958(layer, x, y, text, style);
    return display_text_measure_width(text);
}
