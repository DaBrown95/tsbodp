#include "scene_contact_serial.h"

void scene_contact_handle_serial_irq(void)
{
    unsigned short flags = SCENE_CONTACT_SERIAL_REG16(0x04000140);
    if (((flags & 2) && !(unsigned char)scene_contact_receive_serial_word(
            SCENE_CONTACT_SERIAL_REG32(0x04000150))) ||
        ((flags & 4) && !(unsigned char)scene_contact_transmit_serial_word())) {
        SCENE_CONTACT_SERIAL_REG16(0x04000158) = 0;
        g_scene_contact_input_setup.prefix.fields.status = 6;
        g_scene_contact_input_setup.prefix.fields.state2 = 0;
        g_scene_contact_input_setup.prefix.fields.state3 = 0;
        g_scene_contact_input_setup.prefix.fields.unknown10 = 0;
    }
    if (flags & 1)
        scene_contact_begin_serial_notice();
    SCENE_CONTACT_SERIAL_REG16(0x04000140) = flags;
    g_scene_contact_input_setup.prefix.fields.count = 0;
}
