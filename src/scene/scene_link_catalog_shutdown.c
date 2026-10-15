#include "scene_link_catalog.h"
void scene_link_catalog_shutdown(void)
{
 if(g_frame_flags&0x20)transition_fade_black_out_record(63);
 else transition_run_second(63,0);
 display_release_object_list(&g_frame_primary_list);
 display_reset();display_reset_palette_jobs();display_scene_clear_object_slots();
}
