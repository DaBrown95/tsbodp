#include "scene_phase25.h"
#include "scene.h"
#include "scene_map_selection.h"
#include "display_scene_lifecycle.h"
#include "display_catalog_text.h"
#include "audio_game.h"
#include "resource_commands.h"
#include "scene_request_queue.h"

/* Provisional names for the original row25 resources and saved option byte. */
extern const struct BackgroundResource g_scene_phase25_background3;
extern const struct BackgroundResource g_scene_phase25_background2;
extern const unsigned int g_scene_phase25_background_control0;
extern const unsigned int g_scene_phase25_background_control2;
extern const unsigned int g_scene_phase25_background_control3;
extern unsigned char g_scene_phase25_saved_sample_volume;

void scene_phase25_initialize(void)
{
    int y = 32;
    unsigned int tile = 1;
    const struct BackgroundResource *background = &g_scene_phase25_background3;
    unsigned int limit = 0x7fffffff;
    const char *text;
    unsigned int control;

    display_set_mode(0);
    display_configure_tile_allocation(0);
    display_enable_layers(4096);
    display_show_background(3, g_scene_phase25_background_control3);
    display_load_background(3, background, 0, 0, 0, 0);
    display_show_background(2, g_scene_phase25_background_control2);
    display_load_background_dma(2, &g_scene_phase25_background2, 215, 0, 0, 0);
    display_load_palette((const unsigned char *)background + 2 +
        (g_resource_game_state.scene.unknown_00[0x21] + 3) * 32, 48, 16);
    control = g_scene_phase25_background_control0;
    display_show_background(0, control);
    display_fill_background(0, 0);
    display_load_resource_palette(&g_display_scrolling_palette, 0);
    display_text_set_background_control(control);
    display_text_select_font(3, 12, -1);
    text = display_scene_lookup_text(303);
    while (*text) {
        tile = display_text_draw(tile, 120, y, 118, &text, 1, &limit);
        y += 12;
    }
    transition_run_first(63, 0);
    g_scene_request.unknown_10 = 0;
    g_scene_request.unknown_14 = 0;
    g_scene_phase25_saved_sample_volume = g_audio_game_options.samples_volume;
}

asm(".align 2, 0");
