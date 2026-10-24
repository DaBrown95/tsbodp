#include "frame_actor_attachment_job_68.h"

void frame_finish_attachment_job_68(struct FrameNeedEffectState *owner)
{
    if (save_world_scene_in_selected_row(g_frame_world_id, 1)) {
        if (g_attachment_job_68_refresh_clock == 0) {
            frame_set_animation_frame((struct FrameTickObject *)owner->object,
                g_resource_game_state.scene.counter.value != 0);
            g_attachment_job_68_refresh_clock = 100;
        }
        --g_attachment_job_68_refresh_clock;
    }
}
