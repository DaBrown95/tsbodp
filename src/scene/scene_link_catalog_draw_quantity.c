#include "scene_link_catalog.h"
void scene_link_catalog_draw_quantity(void)
{
 char text[12];
 if(g_scene_request.parameter==1)g_scene_link_catalog_owners.details[1]->flags&=~1u;
 else g_scene_link_catalog_owners.details[1]->flags|=1;
 if(g_scene_request.parameter==g_scene_link_catalog_quantity_limit)g_scene_link_catalog_owners.details[0]->flags&=~1u;
 else g_scene_link_catalog_owners.details[0]->flags|=1;
 display_fill_background_constant_rectangle(0,13,10,4,2,0x90bd);
 display_text_format_number(g_scene_request.parameter,text);
 display_text_draw_line(314,120,80,text,1);
}
asm(".align 2,0");
