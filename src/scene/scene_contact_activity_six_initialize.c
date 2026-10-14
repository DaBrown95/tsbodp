#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_initialize(void) {
 display_show_background(3,g_scene_contact_initial_background_control1);
 display_show_background(2,g_scene_contact_activity_four_background2);
 display_show_background(1,g_scene_contact_activity_four_background1);
 display_load_background(3,&g_scene_contact_activity_six_background3,1,0,0,0);
 display_load_background(2,&g_scene_contact_activity_six_background2,262,0,0,0);
 display_load_background(1,&g_scene_contact_activity_six_background1,263,0,0,0);
 display_load_palette_ranges(&g_scene_contact_activity_six_palette_ranges);
 frame_define_palette_slot(2,g_scene_contact_activity_six_palette2);
 frame_define_palette_slot(3,g_scene_contact_activity_six_palette3);
 frame_define_palette_slot(4,g_scene_contact_activity_six_palette4);
 audio_game_select_activity_callback(1);
 STATE->primary=scene_contact_activity_six_create_primary();
 STATE->secondary=scene_contact_activity_six_create_secondary();
 STATE->gauge=scene_contact_activity_six_create_gauge();
 STATE->saved_sequence_volume=g_audio_game_options.sequences_volume;
 STATE->saved_sample_volume=g_audio_game_options.samples_volume;
 audio_game_set_sequence_volume(255);audio_game_set_sample_volume(128);
 audio_select_sequence(g_scene_contact_activity_six_options[STATE->option].sequence);
}
asm(".align 2,0");
