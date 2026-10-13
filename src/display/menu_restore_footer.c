#include "display_menu_relation_resource.h"
#include "display_menu_primary.h"

void display_menu_restore_footer(void)
{
    display_copy_background_rectangle(1,
        (const struct DisplayStoredMap *)g_display_menu_state.unknown_0c[1],
        27, 12, 27, 12, 3, 2, 0xd116);
}

asm(".align 2, 0");
