#ifndef DISPLAY_TEXT_BANK_H
#define DISPLAY_TEXT_BANK_H
#include "display_text_resource.h"

/* Observed global views; complete surrounding state layout remains unknown. */
extern char *g_display_text_buffer;
extern unsigned char g_display_text_selected_bank;
extern unsigned char g_display_text_bank_value;
extern const void *const g_display_text_banks[];
void display_text_initialize_buffer(void);
/* The table index uses the full input word; the stored selection is a byte. */
void display_text_select_bank(unsigned int);
unsigned int display_text_selected_bank(void);
#endif
