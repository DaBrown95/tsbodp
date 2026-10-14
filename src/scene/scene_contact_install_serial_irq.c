#include "scene_contact_serial.h"
#include "heap.h"

void scene_contact_install_serial_irq(SceneContactNoticeHandler handler,
                                      unsigned int first, unsigned int second)
{
    unsigned short enabled = SCENE_CONTACT_SERIAL_IME;
    unsigned int bytes;
    SCENE_CONTACT_SERIAL_IME = 0;
    heap_clear(&g_scene_contact_input_setup, 0, 48);
    g_scene_contact_input_setup.prefix.fields.first_parameter = first;
    g_scene_contact_input_setup.prefix.fields.second_parameter = second;
    bytes = 514;
    g_scene_contact_input_setup.prefix.fields.first_buffer = heap_allocate(bytes);
    g_scene_contact_input_setup.prefix.fields.second_buffer = heap_allocate(bytes);
    g_scene_contact_input_setup.handler = handler;
    g_scene_contact_input_setup.prefix.fields.flag8 = 1;
    scene_contact_reset_serial_registers();
    set_irq_table_entry(0, (unsigned int)scene_contact_handle_serial_irq);
    SCENE_CONTACT_SERIAL_REG16(0x04000200) |= 0x80;
    g_scene_contact_input_setup.prefix.fields.captured0c =
        g_scene_contact_serial_initial_word;
    g_scene_contact_input_setup.prefix.fields.captured14 =
        g_scene_contact_serial_second_word;
    SCENE_CONTACT_SERIAL_IME = enabled;
}
