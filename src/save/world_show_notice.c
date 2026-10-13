#include "save_world_notices.h"

void save_world_show_notice(unsigned int text_id)
{
    audio_play_animation_cue(3);
    g_actor_scene_result_id.id = text_id;
    save_world_center_notice();
}
