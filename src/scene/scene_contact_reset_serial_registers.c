#include "scene_contact_serial.h"

void scene_contact_reset_serial_registers(void)
{
    unsigned short enabled = SCENE_CONTACT_SERIAL_REG16(0x04000208);
    SCENE_CONTACT_SERIAL_REG16(0x04000208) = 0;
    if (!g_scene_contact_input_setup.prefix.fields.flag8)
        SCENE_CONTACT_SERIAL_REG16(0x04000134) = 0x8000;
    SCENE_CONTACT_SERIAL_REG16(0x04000134) = 0xc000;
    SCENE_CONTACT_SERIAL_REG16(0x04000158) = 0;
    (void)SCENE_CONTACT_SERIAL_REG32(0x04000150);
    SCENE_CONTACT_SERIAL_REG32(0x04000154) = 0;
    SCENE_CONTACT_SERIAL_REG16(0x04000140) = 0x47;
    SCENE_CONTACT_SERIAL_REG16(0x04000202) = 0x80;
    g_scene_contact_input_setup.prefix.fields.count = 0;
    g_scene_contact_input_setup.prefix.fields.status = 0;
    g_scene_contact_input_setup.prefix.fields.state2 = 0;
    g_scene_contact_input_setup.prefix.fields.state3 = 0;
    g_scene_contact_input_setup.prefix.fields.flag8 = 0;
    SCENE_CONTACT_SERIAL_REG16(0x04000208) = enabled;
}
