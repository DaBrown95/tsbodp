#include "display_menu_choice.h"

unsigned char display_menu_test_choice_stamp(struct DisplayMenuSelectionState *record,
                                            const struct DisplayMenuChoiceStamp *current)
{
    record->enabled = 0;
    if (record->major == current->major) {
        if (record->minor == current->minor) {
            if (record->part == (signed char)current->part)
                return 1;
            if (record->part > (signed char)current->part)
                return 1;
            return 0;
        }
        if (record->minor > current->minor)
            return 1;
        return 0;
    }
    if (record->major > current->major)
        return 1;
    return 0;
}
asm(".align 2, 0");
