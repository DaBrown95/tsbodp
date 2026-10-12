#ifndef DISPLAY_TEXT_MEASURE_H
#define DISPLAY_TEXT_MEASURE_H
/* Partial font view; complete storage and glyph encoding remain provisional. */
struct DisplayFont {
    unsigned char height, unknown_01;
    unsigned short first, last;
    unsigned char line_advance, unknown_07;
    const unsigned short *glyph_offsets;
    const unsigned char *widths;
    const unsigned char *glyph_pixels;
};
extern const struct DisplayFont *g_display_fonts[2];
extern unsigned char g_display_text_substitutions[][64];
extern int display_text_measure_width(const char *);
extern int display_text_measure_height(const char *);
extern int display_text_glyph_width(const struct DisplayFont *, unsigned short);
#endif
