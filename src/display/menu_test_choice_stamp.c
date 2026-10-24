#include "display_menu_choice.h"

static inline signed char choice_current_minute(const struct DisplayTimeRecord *current)
{
    return (signed char)*(const unsigned char *)&current->minute;
}

unsigned char display_menu_test_choice_stamp(struct DisplayMenuSelectionState *record,
                                            const struct DisplayTimeRecord *current)
{
    record->enabled = 0;
    if (record->stamp.day == current->day) {
        if (record->stamp.hour == current->hour) {
            if (record->stamp.minute == choice_current_minute(current))
                return 1;
            if (record->stamp.minute > choice_current_minute(current))
                return 1;
            return 0;
        }
        if (record->stamp.hour > current->hour)
            return 1;
        return 0;
    }
    if (record->stamp.day > current->day)
        return 1;
    return 0;
}
asm(".align 2, 0");
