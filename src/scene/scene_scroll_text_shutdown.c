#include "scene_scroll_text.h"
void scene_scroll_text_shutdown(void){transition_run_second(63,0);display_release_object_list(&g_frame_primary_list);display_reset();display_scene_clear_object_slots();}
asm(".align 2,0");
