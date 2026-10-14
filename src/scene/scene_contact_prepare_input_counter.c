#include "scene_contact_serial.h"

unsigned int scene_contact_prepare_input_counter(void)
{
    if (g_scene_contact_input_setup.prefix.fields.count <= 10) {
        SCENE_CONTACT_SERIAL_IME = 0;
        ++g_scene_contact_input_setup.prefix.fields.count;
        SCENE_CONTACT_SERIAL_IME = 1;
        return 0;
    }
    g_scene_contact_input_setup.prefix.fields.pending = 1;
    g_scene_contact_input_setup.prefix.fields.mode = 3;
    scene_contact_reset_serial_registers();
    return 1;
}
