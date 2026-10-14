#include "scene_contact_serial.h"

unsigned int scene_contact_poll_input_status(void)
{
    unsigned short enabled;
    unsigned int mode;
    scene_contact_prepare_input_counter();
    enabled = SCENE_CONTACT_SERIAL_IME;
    SCENE_CONTACT_SERIAL_IME = 0;
    mode = g_scene_contact_input_setup.prefix.fields.status;
    if ((unsigned int)(mode - 4) <= 1)
        g_scene_contact_input_setup.prefix.fields.status = 1;
    SCENE_CONTACT_SERIAL_IME = enabled;
    return mode;
}
