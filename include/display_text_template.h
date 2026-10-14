#ifndef DISPLAY_TEXT_TEMPLATE_H
#define DISPLAY_TEXT_TEMPLATE_H

/* The original template walker advances eight bytes per entry. */
struct DisplayTextTemplateEntry {
    short x, y;
    unsigned char width, style;
    unsigned short text;
};

/* Word arguments are narrowed to sixteen bits; the result is the final tile. */
unsigned int display_text_draw_template(unsigned int, unsigned int,
                                       const struct DisplayTextTemplateEntry *);

#endif
