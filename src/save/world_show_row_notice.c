#include "save_world_display.h"
#include "save_world_notices.h"

void save_world_show_row_notice(unsigned int index)
{
    unsigned int flags = g_save_world_transition_rows[index].flags;
    if (flags & 0x100000) {
        g_actor_scene_result_id.id = 289;
        audio_play_sequence_notification(58);
    } else if (flags & 0x80000) {
        g_actor_scene_result_id.id = 290;
        audio_play_sequence_notification(57);
    }
    save_world_center_notice();
}
