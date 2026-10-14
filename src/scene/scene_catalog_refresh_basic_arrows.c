#include "frame.h"
#include "scene_catalog_paging.h"
void scene_catalog_refresh_basic_arrows(void){
 if(g_scene_catalog_state.selector==4){g_display_scene_frame_objects[11]->flags&=~1U;g_display_scene_frame_objects[12]->flags&=~1U;}
 else {
  if(g_scene_catalog_state.page_start==0)g_display_scene_frame_objects[11]->flags&=~1U;else g_display_scene_frame_objects[11]->flags|=1;
  if(scene_catalog_has_next(g_scene_catalog_state.page_start,g_scene_catalog_state.count))g_display_scene_frame_objects[12]->flags|=1;else g_display_scene_frame_objects[12]->flags&=~1U;
 }
}
asm(".align 2,0");
