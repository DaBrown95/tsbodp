#include "scene_contact_serial.h"
unsigned int scene_contact_emit_serial_word(void)
{
    unsigned short value;
    if (g_scene_contact_input_setup.prefix.fields.transmit_remaining) {
    value = ((unsigned short *)g_scene_contact_input_setup.prefix.fields.second_buffer)
        [g_scene_contact_input_setup.prefix.fields.transmit_index];
    --g_scene_contact_input_setup.prefix.fields.transmit_remaining;
    ++g_scene_contact_input_setup.prefix.fields.transmit_index;
    SCENE_CONTACT_SERIAL_REG32(0x04000154) =
        (scene_contact_fold_serial_word(value) << 24) |
        ((unsigned int)value << 8) | 0xA0;
    } else {
        g_scene_contact_input_setup.prefix.fields.mode = 9;
        return 0;
    }
    return 1;
}
