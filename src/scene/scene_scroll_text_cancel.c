#include "scene_scroll_text.h"
void scene_scroll_text_cancel(void){if(g_scene_previous_request.unknown_00==6)resource_submit_scene(6,0,g_scene_request.scene);else scene_submit_default_request(5);}
asm(".align 2,0");
