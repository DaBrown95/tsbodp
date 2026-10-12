#ifndef DISPLAY_TEXT_DRAW_H
#define DISPLAY_TEXT_DRAW_H
/* The first word is advanced by the tile-rendering consumer; its role is provisional. */
extern unsigned int display_text_draw(unsigned int, int, int, int, const char **,
                                     unsigned int, unsigned int *);
extern unsigned int display_text_draw_line(unsigned int, int, int, const char *,
                                          unsigned int);
extern unsigned int display_text_render(unsigned int, int, int, const char *);
extern unsigned int display_text_draw_block(unsigned int, int, int, int, int,
                                           const char **, unsigned int);
extern unsigned int display_text_draw_limited_line(unsigned int, int, int, int, int,
                                                  const char **, unsigned int,
                                                  unsigned int *);
extern unsigned int display_text_draw_all_lines(unsigned int, int, int, int,
                                               const char *, unsigned int);
#endif
