#ifndef DISPLAY_MENU_CHOICE_H
#define DISPLAY_MENU_CHOICE_H
#include "display_menu_pages.h"

/* Three ordered components occupy four bytes; chronology and ranges are provisional. */
struct DisplayMenuChoiceStamp {
    short major;
    signed char minor;
    unsigned char part;
};
void frame_load_save_value(void *, int);
void frame_write_save_value(const void *, int);
unsigned char display_menu_test_choice_stamp(struct DisplayMenuSelectionState *,
                                             const struct DisplayMenuChoiceStamp *);
void display_menu_save_choice(struct DisplayMenuSelectionState *);
void display_menu_load_choice(struct DisplayMenuSelectionState *);
unsigned char display_menu_choice_enabled(struct DisplayMenuSelectionState *);
#endif
