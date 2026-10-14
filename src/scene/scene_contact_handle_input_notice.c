#include "scene_contact_menu.h"
unsigned int scene_contact_handle_input_notice(unsigned int kind,
                                              unsigned short *first,
                                              unsigned short *second)
{
    switch (kind) {
    case 0x82:
        *second = (g_scene_contact_state->result << 14) |
            ((unsigned short)g_scene_contact_state->amount & 0x3fff);
        *first = 2;
        g_scene_contact_state->result = 0;
        break;
    case 0x43:
        g_scene_contact_state->phase = 6;
        break;
    default:
        return 0;
    }
    return 1;
}
