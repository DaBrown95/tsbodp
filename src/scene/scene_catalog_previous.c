#include "frame.h"
#include "scene_catalog_paging.h"
void scene_catalog_previous(void){
 if(scene_catalog_is_basic_row()) {
  if(g_scene_catalog_state.page_start!=0){g_scene_catalog_state.page_start-=4;scene_catalog_refresh_basic_arrows();}
 } else {
  if(g_scene_catalog_state.row!=0){g_scene_catalog_state.row-=4;scene_catalog_refresh_page_arrows();}
 }
}
asm(".align 2,0");
