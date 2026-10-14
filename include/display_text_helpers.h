#ifndef DISPLAY_TEXT_HELPERS_H
#define DISPLAY_TEXT_HELPERS_H

struct FrameObject;
void display_position_text_object(struct FrameObject *, const char *,
                                  int, int, unsigned int);
char *display_append_text_resource(char *, unsigned int);
/* Normalized C shift domain: digits 0 through 8. Destination bounds are unchecked. */
char *display_format_hex_text(int, int, char *);

#endif
