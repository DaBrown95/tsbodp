#include "scene_contact_serial.h"
unsigned int scene_contact_store_serial_word(unsigned int word)
{
    unsigned short value;
    if (g_scene_contact_input_setup.prefix.fields.receive_remaining) {
        value = word >> 8;
        if ((unsigned char)scene_contact_original_fold_word(value) == word >> 24) {
            ((unsigned short *)g_scene_contact_input_setup.prefix.fields.first_buffer)
                [g_scene_contact_input_setup.prefix.fields.receive_index] = value;
            --g_scene_contact_input_setup.prefix.fields.receive_remaining;
            ++g_scene_contact_input_setup.prefix.fields.receive_index;
            return 1;
        }
        g_scene_contact_input_setup.prefix.fields.mode = 7;
    } else {
        g_scene_contact_input_setup.prefix.fields.mode = 8;
    }
    return 0;
}
