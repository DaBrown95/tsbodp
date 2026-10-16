#ifndef DISPLAY_TEXT_FIELDS_H
#define DISPLAY_TEXT_FIELDS_H
#include "display_text_measure.h"
/* Distinct staging bank; the transfer to active substitutions is unconverted. */
extern unsigned char g_display_text_fields[][64];
extern void display_text_copy_field(const char *, unsigned int);
extern void display_text_copy_field_zero(const char *);
extern void display_text_copy_field_one(const char *);
extern void display_text_copy_field_two(const char *);
extern void display_text_number_field(int, unsigned int);
extern void display_text_number_field_zero(int);
extern void display_text_number_field_one(int);
extern void display_text_number_field_two(int);
extern unsigned int display_text_copy_expanded(const unsigned char *, char *);
extern char *display_text_expand_resource(unsigned int);
extern unsigned char g_display_text_number_separator;
extern char *display_text_format_number(int, char *);
/* String providers used by resource expansion. */
extern char *display_text_copy_string(char *, const char *);
extern unsigned int display_text_string_length(const char *);
extern char *display_text_find_character(const char *, int);
extern void *display_text_move_bytes(void *, const void *, unsigned int);
extern void *display_text_copy_bytes(void *, const void *, unsigned int);
extern const char *display_scene_lookup_text(unsigned int);
#endif
