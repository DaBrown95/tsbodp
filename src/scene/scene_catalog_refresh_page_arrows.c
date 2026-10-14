#include "frame.h"
#include "scene_catalog_paging.h"
void scene_catalog_refresh_page_arrows(void){
 if(g_scene_catalog_state.row==0)g_display_scene_frame_objects[13]->flags&=~1U;else g_display_scene_frame_objects[13]->flags|=1;
 if(scene_catalog_has_next(g_scene_catalog_state.row,g_scene_catalog_state.value))g_display_scene_frame_objects[14]->flags|=1;else g_display_scene_frame_objects[14]->flags&=~1U;
}
asm(".align 2,0");
