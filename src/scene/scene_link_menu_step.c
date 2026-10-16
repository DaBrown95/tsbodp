#include "scene_link_menu.h"
#include "input.h"
#include "event_record.h"

void scene_link_menu_step(void)
{
    struct EventPayload payload;
    unsigned int pressed;

    if (g_frame_flags & 0x20) {
        if ((unsigned char)transition_link_update() == 1) {
            g_frame_flags &= ~0x20u;
            if (g_scene_request.unknown_10 == 2)
                g_scene_request.unknown_10 = 0;
            scene_link_menu_draw_status();
        } else {
            *(unsigned int *)payload.storage.bytes = 0;
            transition_record_event(1, payload);
            if ((g_link_flags & 0x2000) && (g_link_flags & 0x4000)) {
                resource_submit_scene(1, 2, g_frame_world_id);
                g_link_flags &= 0xffff9fffu;
            }
        }
    }
    if (g_scene_request.unknown_10 != 2) {
        pressed = g_input_local_pressed[g_input_config.local_player];
        if (pressed & 1)
            scene_link_menu_accept();
        else if (pressed & 0xc0)
            scene_link_menu_change_row();
        else {
            unsigned int mask = 6;
            mask &= pressed;
            if (mask)
                scene_link_menu_cancel();
        }
    }
}
asm(".align 2,0");
