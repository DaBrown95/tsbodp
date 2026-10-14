#include "scene_catalog_content.h"
unsigned int scene_catalog_basic_value(unsigned int kind) {
 if((kind<=117&&kind!=63)||kind==210||
  (kind==143&&(g_scene_catalog_state.selector==3||g_scene_catalog_state.selector==12))||
  (kind==125&&g_scene_catalog_state.selector==8)||
  (kind==63&&g_scene_catalog_state.selector==0)||
  (kind==129&&g_scene_catalog_state.selector==3))
  return (g_display_scene_catalog[kind].number_value*g_scene_catalog_value_rates[g_scene_catalog_state.selector].basic)>>16;
 return 0;
}
asm(".align 2,0");
