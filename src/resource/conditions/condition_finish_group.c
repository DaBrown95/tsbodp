#include "resource_commands.h"
#include "resource_conditions.h"

extern unsigned int g_condition_group_display_kinds[];
extern int condition_query_actor(void *, int);
extern void condition_update_actor(void *, int, int);

static inline unsigned int group_address(unsigned int row, unsigned int column)
{
    unsigned int base = (unsigned int)&g_resource_game_state;
    unsigned int offset = column * 24;
    offset += row * 144;
    return offset + base;
}

void condition_finish_group(unsigned int row, unsigned int column)
{
    unsigned int all = 1;
    *(unsigned char *)(group_address(row, column) + 0x445) = 1;
    if (row == 2 && column == 0) {
        unsigned char *game = (unsigned char *)&g_resource_game_state;
        void **actor = (void **)(game + 0xf0);
        int value = (signed char)condition_query_actor(*actor, 0x7c);
        condition_update_actor(*actor, value, 1);
    }
    {
        unsigned int index = 0;
        for (; index < 5; index++) {
            if (!*(unsigned char *)(group_address(row, index) + 0x445)) {
                all = 0;
                break;
            }
        }
    }
    if (all && column != 5) {
        if (row != 4) {
            unsigned int kind = g_condition_group_display_kinds[row];
            if (kind != 0xff)
                resource_set_display_kind(kind);
        } else {
            condition_activate_entry(4, 5, 0);
            condition_activate_entry(4, 5, 1);
            condition_activate_entry(4, 5, 2);
            condition_activate_entry(4, 5, 3);
        }
    }
}
asm(".align 2, 0");
