#ifndef DISPLAY_TEXT_RUNTIME_H
#define DISPLAY_TEXT_RUNTIME_H

void *display_text_copy_bytes(void *, const void *, unsigned int);
void *display_text_move_bytes(void *, const void *, unsigned int);
void *display_fill_bytes(void *, int, unsigned int);
char *display_text_copy_string(char *, const char *);
char *display_text_append_string(char *, const char *);
unsigned int display_text_string_length(const char *);

#endif
