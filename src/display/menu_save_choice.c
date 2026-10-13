#include "display_menu_choice.h"

void display_menu_save_choice(struct DisplayMenuSelectionState *record)
{
    if (!record->enabled) {
        record->definition = 24;
        record->text_kind = 24;
    }
    frame_write_save_value(&record->major, 4);
    frame_write_save_value(&record->definition, 1);
    frame_write_save_value(&record->text_kind, 1);
}
asm(".align 2, 0");
