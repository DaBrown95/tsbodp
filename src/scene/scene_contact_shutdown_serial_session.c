#include "scene_contact_serial_session_controller.h"

void scene_contact_shutdown_serial_session(void)
{
    if (scene_queued_request_kind() != 20)
        scene_contact_stop_serial_input();
    heap_free(g_scene_contact_serial_session.buffer0c);
    transition_run_second(63, 0);
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_reset_palette_jobs();
    display_scene_clear_object_slots();
}
