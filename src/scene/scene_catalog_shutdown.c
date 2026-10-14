#include "scene_catalog.h"
void scene_catalog_shutdown(void) {
 transition_run_second(63,0);
 display_release_object_list(&g_scene_catalog_objects);
 display_reset();
 display_reset_palette_jobs();
 display_scene_clear_object_slots();
}
asm(".align 2,0");
