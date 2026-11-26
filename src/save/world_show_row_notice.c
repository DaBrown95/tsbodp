#include "save_world_display.h"
#include "save_world_notices.h"

void save_world_show_row_notice(unsigned int index)
{
    unsigned int flags = g_save_world_transition_rows[index].flags;
#if TSBO_REVISION == 1
    unsigned char width, height;
#endif
    if (flags & 0x100000) {
        g_actor_scene_result_id.id = 289;
        audio_play_sequence_notification(58);
    } else if (flags & 0x80000) {
        g_actor_scene_result_id.id = 290;
        audio_play_sequence_notification(57);
    }
#if TSBO_REVISION == 0
    save_world_center_notice();
#else
    /* Revision 1 selects the font first and centres within 28 tiles,
     * rounding the height up. */
    display_text_select_font(3, 0, -1);
    width = display_text_measure_width(display_scene_lookup_text(g_actor_scene_result_id.id));
    height = display_text_measure_height(display_scene_lookup_text(g_actor_scene_result_id.id));
    ((struct FrameActorParameterNotification *)&g_actor_scene_request)->active = 0;
    ((struct FrameActorParameterNotification *)&g_actor_scene_request)->x = (28 - (width >> 3)) / 2;
    ((struct FrameActorParameterNotification *)&g_actor_scene_request)->y = 7 - ((height + 7) / 16);
    scene_submit_default_request(2);
#endif
}
