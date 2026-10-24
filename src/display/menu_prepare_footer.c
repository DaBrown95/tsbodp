#include "display_menu_results.h"
#include "display_scene_redraw.h"
#include "save_world_display.h"
#include "display_transient_definition.h"
#include "display_condition_panel_details.h"

extern struct FrameSpriteResource g_menu_footer_slot4, g_menu_footer_slot5;
extern struct FrameSpriteResource g_menu_footer_slot6, g_menu_footer_slot7;
extern const unsigned short g_menu_footer_palette5[], g_menu_footer_palette6[];
extern const unsigned short g_menu_footer_palette7[], g_menu_footer_palette8[];
static inline void footer_caption_values(unsigned int style, const char *text,
                                         int x, int y, unsigned int tile)
{
    display_text_draw_line(tile, x, y, text, style);
}
void display_menu_prepare_footer(void)
{
    struct { signed int x:16, y:16; } position;
    int relation;
    {
        struct DisplayMenuObjects *objects;
        struct FrameObject *indicator;
        g_display_menu_objects.unknown_00[0] = (unsigned int)frame_create_scene_object(32, 8, 1, 1);
        objects = &g_display_menu_objects;
        ((struct FrameObject *)objects->unknown_00[0])->flags &= ~16;
        objects->unknown_00[1] = (unsigned int) frame_create_scene_object(33, 9, 2, 1);
        ((struct FrameObject *)objects->unknown_00[1])->flags &= ~1;
        position.x = 238;
        position.y = 96;
        display_text_set_background_control(g_display_menu_control1);
        {
            register struct DisplayMenuState *menu asm("r0") = &g_display_menu_state;
            unsigned int definition;
            indicator = (struct FrameObject *)objects->unknown_00[0];
            definition = menu->definition;
            relation = display_menu_read_relation(&g_display_menu_relation_values,
                                                  definition);
        }
        if (relation > 0) {
            register int numerator asm("r0") = relation;
            register unsigned int percent asm("r1") = (unsigned int)save_world_ratio_percent(numerator, 100) << 16;
            percent >>= 16;
            frame_set_animation_frame((struct FrameTickObject *)indicator,
                save_world_scale_percent(10, percent) + 10);
        } else {
            register int numerator asm("r0") = relation;
            int denominator = -100;
            register unsigned int percent asm("r1") = (unsigned int)save_world_ratio_percent(numerator, denominator) << 16;
            percent >>= 16;
            frame_set_animation_frame((struct FrameTickObject *)indicator,
                10 - save_world_scale_percent(10, percent));
        }
    }
    {
        register unsigned int font_group asm("r0") = 0;
        register int font_palette asm("r1") = 0;
        display_text_select_font(font_group, font_palette, -1);
    }
    display_text_number_field_zero(relation);
    {
        const char *caption = display_scene_lookup_text(6222);
        footer_caption_values(2, caption, position.x, position.y, 442);
    }
    display_text_copy_field_zero((const char *)&g_display_menu_relation_state);
    {
        struct DisplayMenuObjects *objects;
        g_display_menu_objects.hint = frame_create_scene_object(34, 234, 3, 1);
        objects = &g_display_menu_objects;
        objects->hint->flags &= ~1;
        objects->unknown_0c = (unsigned int) frame_create_scene_object(35, 269, 4, 1);
        ((struct FrameObject *)objects->unknown_0c)->flags &= ~1;
        objects->scroll = frame_create_scene_object(36, 268, 4, 1);
        objects->scroll->flags &= ~1;
        objects->first = frame_create_scene_object(37, 269, 4, 1);
        objects->first->flags &= ~1;
        objects->second = frame_create_scene_object(38, 268, 4, 1);
        objects->second->flags &= ~1;
    }
    frame_initialize_transient_definition(0, 6, &g_menu_footer_slot6);
    frame_initialize_transient_definition(0, 7, &g_menu_footer_slot7);
    frame_initialize_transient_definition(0, 4, &g_menu_footer_slot4);
    frame_initialize_transient_definition(0, 5, &g_menu_footer_slot5);
    display_load_palette_alternate(g_menu_footer_palette5, 80, 16);
    display_load_palette_alternate(g_menu_footer_palette6, 96, 16);
    display_load_palette_alternate(g_menu_footer_palette7, 112, 16);
    display_load_palette_alternate(g_menu_footer_palette8, 128, 16);
    display_text_set_background_control(g_display_menu_control0);
}
asm(".align 2, 0");
