#include "frame.h"
#include "scene_catalog_paging.h"
void scene_catalog_next(void){
 if(scene_catalog_is_basic_row()) {
  if(scene_catalog_has_next(g_scene_catalog_state.page_start,g_scene_catalog_state.count)){g_scene_catalog_state.page_start+=4;scene_catalog_refresh_basic_arrows();}
 } else {
  if(scene_catalog_has_next(g_scene_catalog_state.row,g_scene_catalog_state.value)){g_scene_catalog_state.row+=4;scene_catalog_refresh_page_arrows();}
 }
}
asm(".align 2,0");
