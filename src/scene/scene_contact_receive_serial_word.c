#include "scene_contact_serial.h"
unsigned int scene_contact_receive_serial_word(unsigned int word)
{
    unsigned int command;
    unsigned short receive_bytes, send_bytes, complete_bytes;
    if (!g_scene_contact_input_setup.prefix.fields.state2) {
        if (g_scene_contact_input_setup.prefix.fields.state3 == 2) {
            if (word == g_scene_contact_input_setup.prefix.fields.captured14) {
                SCENE_CONTACT_SERIAL_REG16(0x04000158) = 0x30;
                g_scene_contact_input_setup.prefix.fields.unknown10 = word;
                g_scene_contact_input_setup.prefix.fields.status = 1;
                g_scene_contact_input_setup.prefix.fields.state2 = 1;
                g_scene_contact_input_setup.prefix.fields.unknown06 = 0;
                g_scene_contact_input_setup.prefix.fields.pending = 0;
            }
            g_scene_contact_input_setup.prefix.fields.state3 = 0;
        } else {
            g_scene_contact_input_setup.prefix.fields.mode = 2;
            return 0;
        }
    } else {
        command = word & 0xFF;
        if (!g_scene_contact_input_setup.prefix.fields.unknown06) {
            if (command > 63 && command <= g_scene_contact_input_setup.prefix.fields.first_parameter) {
                g_scene_contact_input_setup.prefix.fields.receive_index = 0;
                g_scene_contact_input_setup.prefix.fields.receive_remaining = (word >> 8) & 0xFF;
                if (!g_scene_contact_input_setup.prefix.fields.receive_remaining) {
                    receive_bytes = 0;
                    g_scene_contact_input_setup.handler(command, &receive_bytes,
                        g_scene_contact_input_setup.prefix.fields.first_buffer);
                    g_scene_contact_input_setup.prefix.fields.status = 4;
                } else {
                    g_scene_contact_input_setup.prefix.fields.status = 2;
                    g_scene_contact_input_setup.prefix.fields.unknown06 = command;
                }
                SCENE_CONTACT_SERIAL_REG32(0x04000154) =
                    (scene_contact_fold_serial_word(g_scene_contact_input_setup.prefix.fields.receive_remaining) << 24) |
                    (g_scene_contact_input_setup.prefix.fields.receive_remaining << 8) | command;
            } else if (command > 127 && command <= g_scene_contact_input_setup.prefix.fields.second_parameter) {
                g_scene_contact_input_setup.prefix.fields.status = 3;
                g_scene_contact_input_setup.prefix.fields.unknown06 = command;
                g_scene_contact_input_setup.handler(command, &send_bytes,
                    g_scene_contact_input_setup.prefix.fields.second_buffer);
                g_scene_contact_input_setup.prefix.fields.transmit_index = 0;
                g_scene_contact_input_setup.prefix.fields.transmit_remaining = (send_bytes + 1) / 2;
                SCENE_CONTACT_SERIAL_REG32(0x04000154) =
                    (scene_contact_fold_serial_word(g_scene_contact_input_setup.prefix.fields.transmit_remaining) << 24) |
                    (g_scene_contact_input_setup.prefix.fields.transmit_remaining << 8) | command;
            }
        } else if (g_scene_contact_input_setup.prefix.fields.unknown06 > 63 &&
                   g_scene_contact_input_setup.prefix.fields.unknown06 <=
                       g_scene_contact_input_setup.prefix.fields.first_parameter) {
            if (command == 0x60) {
                if ((unsigned char)scene_contact_store_serial_word(word)) {
                    if (!g_scene_contact_input_setup.prefix.fields.receive_remaining) {
                        complete_bytes = g_scene_contact_input_setup.prefix.fields.receive_index * 2;
                        g_scene_contact_input_setup.handler(
                            g_scene_contact_input_setup.prefix.fields.unknown06, &complete_bytes,
                            g_scene_contact_input_setup.prefix.fields.first_buffer);
                        SCENE_CONTACT_SERIAL_REG32(0x04000154) =
                            (scene_contact_fold_serial_word(0) << 24) |
                            g_scene_contact_input_setup.prefix.fields.unknown06;
                        g_scene_contact_input_setup.prefix.fields.status = 4;
                        g_scene_contact_input_setup.prefix.fields.unknown06 = 0;
                    }
                } else {
                    return 0;
                }
            } else {
                g_scene_contact_input_setup.prefix.fields.mode = 6;
                return 0;
            }
        } else {
            g_scene_contact_input_setup.prefix.fields.mode = 4;
            return 0;
        }
    }
    return 1;
}

asm(".align 2, 0");
