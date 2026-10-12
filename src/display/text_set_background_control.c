#include "display_text_raster.h"

union TextBackgroundControl {
    unsigned int raw;
    struct {
        unsigned int unknown_00 : 2, tile_block : 2, unknown_04 : 3;
        unsigned short wide_color : 1;
        unsigned int map_block : 5, unknown_13 : 19;
    } bits;
};

void display_text_set_background_control(unsigned int control)
{
    union TextBackgroundControl view;
    unsigned short *map;
    unsigned char *tiles;
    view.raw = control;
    map = (void *)(0x06000000 + view.bits.map_block * 0x800);
    tiles = (void *)(0x06000000 + view.bits.tile_block * 0x4000);
    g_display_text_state.map = map;
    g_display_text_state.map_current = map;
    g_display_text_state.tiles = tiles;
    g_display_text_state.tile_bytes = (view.bits.wide_color + 1) << 5;
    g_display_text_state.wide_color = view.bits.wide_color;
}
