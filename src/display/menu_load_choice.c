#include "display_menu_choice.h"

void display_menu_load_choice(struct DisplayMenuSelectionState *record)
{
    frame_load_save_value(&record->major, 4);
    frame_load_save_value(&record->definition, 1);
    frame_load_save_value(&record->text_kind, 1);
    if (record->text_kind != 24 && record->definition != 24)
        record->enabled = 1;
}
asm(".align 2, 0");
