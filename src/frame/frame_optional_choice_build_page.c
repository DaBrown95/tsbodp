#include "frame_optional_choice_list.h"

unsigned char frame_optional_choice_build_page(void)
{
    unsigned char count = 1, index;
    g_need_effect_choice_text[0] = 496;
    {
        unsigned char *initial_page = &g_optional_choice_page;
        unsigned char *page;
        int limit;
        index = *initial_page;
        limit = *initial_page + 4;
        page = initial_page;
        if (index < limit)
            while (index != 24 && (signed char)g_optional_choice_values[index].value != -1) {
                g_need_effect_choice_text[count] =
                    (signed char)g_optional_choice_values[index].value + 6025;
                count++;
                index++;
                if (index >= *page + 4)
                    break;
            }
    }
    return count;
}
