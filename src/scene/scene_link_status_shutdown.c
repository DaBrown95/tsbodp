#include "scene_link_status_private.h"
void scene_link_status_shutdown(void)
{
 transition_fade_black_out_record(63);
 display_release_object_list(&g_frame_primary_list);
 display_reset();
 display_reset_palette_jobs();
}
asm(".align 2,0");
