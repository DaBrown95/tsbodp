#include "scene_startup.h"

void scene_initialize_transient_slots(void) {
 if(g_scene_id<=14)frame_initialize_transient_definition(0,2,&g_scene_startup_transient2);
 frame_initialize_transient_definition(0,3,&g_scene_startup_transient3);
 frame_initialize_transient_definition(0,6,&g_scene_startup_transient6);
 frame_initialize_transient_definition(0,7,&g_scene_startup_transient7);
}
asm(".align 2,0");
