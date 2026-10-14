#include "frame.h"
#include "scene_catalog_paging.h"
unsigned char scene_catalog_is_basic_row(void){return g_scene_request.scene<g_scene_catalog_action_row;}
asm(".align 2,0");
