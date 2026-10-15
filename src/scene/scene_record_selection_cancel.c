#include "scene_record_selection.h"
void scene_record_selection_cancel(void)
{
 scene_submit_default_request(g_scene_link_menu_selector_word);
 audio_play_animation_cue(2);
}
