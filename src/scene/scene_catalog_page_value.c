#include "scene_catalog_content.h"
unsigned int scene_catalog_page_value(unsigned int kind) {
 return (g_display_scene_catalog[kind].number_value*g_scene_catalog_value_rates[g_scene_catalog_state.selector].page)>>16;
}
asm(".align 2,0");
