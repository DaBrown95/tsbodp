#ifndef DISPLAY_TEXT_MEASURE_H
#define DISPLAY_TEXT_MEASURE_H
/* Partial font view; complete storage and glyph encoding remain provisional. */
struct DisplayFont {
    unsigned char height, unknown_01;
    unsigned short first, last, unknown_06;
    unsigned int unknown_08;
    const unsigned char *widths;
};
extern const struct DisplayFont *g_display_fonts[2];
extern unsigned char g_display_text_substitutions[][64];
extern int display_text_measure_width(const char *);
extern int display_text_measure_height(const char *);
extern int display_text_glyph_width(const struct DisplayFont *, unsigned short);
#endif
