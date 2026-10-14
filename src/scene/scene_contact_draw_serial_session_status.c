#include "scene_contact_serial_session_controller.h"

void scene_contact_draw_serial_session_status(unsigned int index)
{
    unsigned short text = g_scene_contact_serial_messages[index].text;
    if (g_scene_contact_serial_session.initial00 != text) {
        if (!g_scene_contact_serial_session.unknown02 || index == 2 || index == 3) {
            display_fill_background_constant_rectangle(0, 5, 10, 20, 2, 0);
            display_text_select_font(3, 0, 0);
            display_text_draw_line(57, 120, 84, display_scene_lookup_text(text), 1);
            g_scene_contact_serial_session.unknown02 = g_scene_contact_serial_messages[index].delay;
            g_scene_contact_serial_session.initial00 = text;
            if (g_display_scene_frame_objects[2]) {
                if (index == 2) {
                    frame_set_animation_commands(g_display_scene_frame_objects[2], g_scene_contact_serial_animation_commands + 2, 0);
                    g_display_scene_frame_objects[2]->render_special = 0;
                } else if (index == 3) {
                    frame_set_animation_commands(g_display_scene_frame_objects[2], g_scene_contact_serial_animation_commands + 2, 0);
                    g_display_scene_frame_objects[2]->render_special = 1;
                }
            }
        } else
            --g_scene_contact_serial_session.unknown02;
        if (index == 1 && !(index & g_save_stream_state.header.words[6])) {
            register unsigned int flags asm("r0");
            flags = index;
            flags |= g_save_stream_state.header.words[6];
            g_save_stream_state.header.words[6] = flags;
        }
    }
    text = g_scene_contact_serial_session.status04;
    if (g_scene_contact_serial_session.status06 != text) {
        g_scene_contact_serial_session.status06 = text;
        display_fill_background_constant_rectangle(0, 5, 13, 20, 2, 0);
        if (text <= 6658) {
            display_text_select_font(3, 0, 0);
            display_text_draw_line(137, 120, 104, display_scene_lookup_text(text), 1);
        }
    }
}
