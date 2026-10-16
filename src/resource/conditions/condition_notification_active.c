#include "resource_conditions.h"
#include "scene_request.h"
#include "display_menu.h"

unsigned char condition_notification_active(unsigned int kind)
{
    if (g_scene_request.unknown_00 != 15 ||
        g_display_menu_state.definition != kind)
        return 0;
    return 1;
}

/* The following function starts on the original word boundary. */
asm(".align 2, 0");
