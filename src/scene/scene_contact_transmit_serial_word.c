#include "scene_contact_serial.h"
unsigned int scene_contact_transmit_serial_word(void)
{
    if (!g_scene_contact_input_setup.prefix.fields.state2) {
        if (g_scene_contact_input_setup.prefix.fields.state3 == 1)
            g_scene_contact_input_setup.prefix.fields.state3 = 2;
        else {
            g_scene_contact_input_setup.prefix.fields.mode = 1;
            return 0;
        }
    } else if (g_scene_contact_input_setup.prefix.fields.unknown06 &&
        (g_scene_contact_input_setup.prefix.fields.unknown06 <= 63 ||
         g_scene_contact_input_setup.prefix.fields.unknown06 >
             g_scene_contact_input_setup.prefix.fields.first_parameter)) {
        if ((signed char)g_scene_contact_input_setup.prefix.fields.unknown06 < 0 &&
            g_scene_contact_input_setup.prefix.fields.unknown06 <=
                g_scene_contact_input_setup.prefix.fields.second_parameter) {
            if ((unsigned char)scene_contact_emit_serial_word()) {
            unsigned int remaining = g_scene_contact_input_setup.prefix.fields.transmit_remaining;
            if (!remaining) {
                g_scene_contact_input_setup.prefix.fields.status = 5;
                g_scene_contact_input_setup.prefix.fields.unknown06 = remaining;
            }
            } else { return 0; }
        } else {
            g_scene_contact_input_setup.prefix.fields.mode = 5;
            return 0;
        }
    }
    return 1;
}

asm(".align 2, 0");
