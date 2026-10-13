#include "display_time_daily.h"
#include "frame_random.h"

void display_menu_relax_relation_values(struct DisplayMenuRelationValues *values)
{
    unsigned int index = 0;
    int sentinel = -128;
    unsigned char *cursor = (unsigned char *)values;
    for (; index <= 23; ++index) {
        unsigned int positive;
        if (*(signed char *)(cursor + 9) == sentinel ||
            *(signed char *)(cursor + 9) == 0)
            goto next;
        if (*(signed char *)(cursor + 9) > 0) {
            positive = 1;
            *(signed char *)(cursor + 9) -= frame_random_range(0, 2);
        } else {
            positive = 0;
            *(signed char *)(cursor + 9) += frame_random_range(0, 2);
        }
        if ((*(signed char *)(cursor + 9) > 0 && positive == 0) ||
            (*(signed char *)(cursor + 9) < 0 && positive == 1))
            *(signed char *)(cursor + 9) = 0;
next:
        cursor += sizeof(struct DisplayMenuRelationRecord);
    }
}
