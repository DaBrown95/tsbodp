#include "scene_contact_serial_session_controller.h"

void scene_contact_commit_serial_session(void)
{
    display_fill_background_constant_rectangle(0, 5, 10, 20, 5, 0);
    display_text_select_font(3, 0, 0);
    display_text_draw_line(57, 120, 84, display_scene_lookup_text(256), 1);
    save_stream_commit_slot(3);
}
