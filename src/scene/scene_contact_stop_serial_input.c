#include "scene_contact_serial_session_controller.h"

void scene_contact_stop_serial_input(void)
{
    unsigned short enabled = SCENE_CONTACT_SERIAL_IME;
    SCENE_CONTACT_SERIAL_IME = 0;
    SCENE_CONTACT_SERIAL_REG16(0x04000134) = 0x8000;
    SCENE_CONTACT_SERIAL_REG16(0x04000158) = 0;
    (void)SCENE_CONTACT_SERIAL_REG32(0x04000150);
    SCENE_CONTACT_SERIAL_REG16(0x04000140) = 0x47;
    SCENE_CONTACT_SERIAL_REG16(0x04000200) &= 0xff7f;
    g_scene_contact_input_setup.prefix.fields.count = 0;
    SCENE_CONTACT_SERIAL_IME = enabled;
    restore_irq_table_entry(0);
    heap_free(g_scene_contact_input_setup.prefix.fields.second_buffer);
    heap_free(g_scene_contact_input_setup.prefix.fields.first_buffer);
    heap_clear(&g_scene_contact_input_setup, 0, 48);
}
