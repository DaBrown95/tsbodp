#ifndef DISPLAY_MENU_H
#define DISPLAY_MENU_H

/* Partial views: five observed row slots, no complete state/table bound. */
struct DisplayMenuState {
    unsigned int unknown_00, definition, record_group, unknown_0c[2];
    unsigned char codes[5], parameters[5], positions[6];
    unsigned char resource_shown, choice, unknown_26, unknown_27;
    unsigned char unknown_28, unknown_29, unknown_2a, unknown_2b;
};
struct DisplayMenuTextRecord {
    unsigned short text, unknown_02;
    unsigned char entries[5], unknown_09[15];
};
extern struct DisplayMenuState g_display_menu_state;
extern const struct DisplayMenuTextRecord *g_display_menu_text_records[];
void display_menu_draw_lines(void);
void display_menu_initialize(void);

#endif
