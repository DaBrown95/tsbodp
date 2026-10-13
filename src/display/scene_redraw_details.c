#include "display_scene_catalog_render.h"
/* The category view is addressed separately from the record cursor. */
static __inline unsigned int catalog_category(const struct DisplayCatalogItem *base,
                                              unsigned int byte_offset)
{
    unsigned int address = (unsigned int)&base->category;
    byte_offset += address;
    return *(const unsigned int *)byte_offset;
}
void display_scene_redraw_details(unsigned char page)
{
    unsigned int ordinal = 0, i;
    unsigned char offset = 0;
    const struct DisplayCatalogItem *record;
    unsigned int record_offset;
    int no_index;
    unsigned int style;
    const struct DisplayCatalogItem *catalog;
    struct DisplaySceneRequestState *request;
    if (page) offset = page << 2;
    display_scene_clear_detail_background();
    display_text_set_background_control(g_display_scrolling_layer_control0);
    display_text_select_font(3, 0, -1);
    i = 0;
    catalog = g_display_scene_catalog;
    request = &g_display_scene_request_state;
    no_index = -1;
    style = i;
    record = catalog;
    record_offset = 0;
    for (; i <= 148; ++record, record_offset += 24, ++i) {
        if (catalog_category(catalog, record_offset) == request->scene && record->id != 0x13d && display_scene_item_enabled(g_display_scene_item_mask, i)) {
            if (ordinal == request->parameter + offset) {
                int position = display_catalog_draw_name(1, 8, 0x5a, i, no_index, style);
                const char *text;
                display_text_number_field_zero(record->number_value);
                text = display_scene_lookup_text(0x184d);
                position += 0x12;
                display_text_draw_line(0x3d, position, 0x5a, text, style);
                display_text_select_font(1, 0, no_index);
                display_catalog_draw_details(0x51, 8, 0x6e, 0xe0, i, no_index, style);
                break;
            }
            ++ordinal;
        }
    }
}

/* Zero-filled alignment belongs to the original linked extent. */
asm(".align 2, 0");
