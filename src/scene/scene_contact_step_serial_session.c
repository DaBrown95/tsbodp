#include "scene_contact_serial_session_controller.h"

void scene_contact_step_serial_session(void)
{
    scene_contact_draw_serial_session_status(scene_contact_poll_input_status());
    switch (g_scene_request.unknown_10) {
    case 0:
        if (g_scene_contact_input_pressed[g_scene_contact_serial_player_input.input_index31] & 2)
            resource_submit_scene(5, 1, 1);
        break;
    case 1:
        if (!--g_scene_request.unknown_14)
            resource_submit_scene(20, g_scene_request.mode, 2);
        break;
    case 2:
        if (!--g_scene_request.unknown_14) {
            unsigned char *destination;
            union SceneContactSerialRecord *input;
            if (!g_scene_contact_serial_session.matched08) {
                save_world_reset_defaults();
                g_frame_world_id = 6;
                g_scene_contact_serial_player_input.flags07 = 4;
                g_scene_contact_serial_player_input.value08 = 348;
                g_scene_contact_serial_player_input.value0a = 367;
                save_world_initialize();
            }
            destination = &g_scene_contact_serial_capture.bytes[16];
            input = g_scene_contact_serial_session.buffer0c;
            ((union SceneContactSerialCapture *)(destination - 16))->words[0] = input->words[0];
            ((union SceneContactSerialCapture *)(destination - 16))->words[1] = input->words[1];
            heap_copy(destination, input->bytes + 8, 16);
            heap_clear(destination + 8, 0, 8);
            heap_copy(destination + 16, input->bytes + 24, 8);
            heap_copy(destination + 24, input->bytes + 32, 8);
            heap_copy(destination + 136, input->bytes + 40, 24);
            heap_copy(destination + 160, input->bytes + 64, 44);
            scene_contact_commit_serial_session();
            resource_submit_scene(1, 5, 0);
        }
        break;
    case 3:
        if (!--g_scene_request.unknown_14) {
            heap_clear(&g_scene_contact_serial_capture.bytes[16], 0, 16);
            scene_contact_commit_serial_session();
            g_scene_contact_serial_session.status04 = 6659;
            g_scene_request.unknown_10 = 0;
        }
        break;
    case 4:
        break;
    }
}
