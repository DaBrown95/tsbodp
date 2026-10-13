#include "save_world_display.h"
#include "save_world_notices.h"

void save_world_show_row_flag_notice(unsigned int index)
{
    if (g_save_world_transition_rows[index].flags & 0x40000) {
        g_actor_scene_result_id.id = 291;
        audio_play_sequence_notification(58);
    }
    save_world_center_notice();
}
