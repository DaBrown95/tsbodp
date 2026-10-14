#include "scene_contact_serial.h"

void scene_contact_begin_serial_notice(void)
{
    (void)SCENE_CONTACT_SERIAL_REG32(0x04000150);
    SCENE_CONTACT_SERIAL_REG32(0x04000154) =
        g_scene_contact_input_setup.prefix.fields.captured0c;
    SCENE_CONTACT_SERIAL_REG16(0x04000158) = 0x20;
    g_scene_contact_input_setup.prefix.fields.status = 0;
    g_scene_contact_input_setup.prefix.fields.state2 = 0;
    g_scene_contact_input_setup.prefix.fields.state3 = 1;
}
