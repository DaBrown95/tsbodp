#ifndef DISPLAY_TEXT_RASTER_H
#define DISPLAY_TEXT_RASTER_H
#include "display_text_measure.h"
#include "display_text_draw.h"
/* Known fields from the connected font/buffer producers and tile consumers. */
struct DisplayFontResource {
    const unsigned char *data;
    unsigned int line_advance;
};
struct DisplayTextRasterState {
    const struct DisplayFont *font, *alternate_font;
    unsigned int palette_base;
    int fill;
    unsigned int palette_bits;
    int line_height;
    unsigned short *map, *map_current;
    unsigned char *tiles;
    unsigned int tile_bytes, wide_color, unknown_2c;
    void *work;
    unsigned int dirty, pixel_mode;
};
extern const struct DisplayFontResource g_display_font_resources[];
extern struct DisplayFont g_display_font_banks[][2];
extern struct DisplayTextRasterState g_display_text_state;
extern void display_text_load_font(unsigned int, unsigned int);
extern void display_text_select_font(unsigned int, int, int);
extern void display_text_set_buffers(void *, void *, unsigned int);
extern void display_text_set_background_control(unsigned int);
extern void display_text_initialize(void);
extern unsigned short *display_text_map_position(unsigned short *, int, int);
extern void display_text_fill_rows(unsigned int *, unsigned int, unsigned int);
extern void display_text_read_rows(unsigned int *, unsigned int,
                                   const unsigned short *, const void *);
extern void display_text_emit_rows(const unsigned int *, unsigned int,
                                   unsigned short *, void *, unsigned int);
extern void display_text_flip_tile(void *);
#endif
