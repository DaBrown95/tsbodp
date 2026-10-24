#ifndef DISPLAY_MENU_CHOICE_H
#define DISPLAY_MENU_CHOICE_H
#include "display_menu_pages.h"
#include "save_stream.h"

/* Observed clock comparison; chronology and ranges remain provisional. */
unsigned char display_menu_test_choice_stamp(struct DisplayMenuSelectionState *,
                                             const struct DisplayTimeRecord *);
void display_menu_save_choice(struct DisplayMenuSelectionState *);
void display_menu_load_choice(struct DisplayMenuSelectionState *);
unsigned char display_menu_choice_enabled(struct DisplayMenuSelectionState *);
#endif
