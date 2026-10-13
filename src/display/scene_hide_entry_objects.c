#include "display_scene_entry_cleanup.h"
#include "display_scene_lifecycle.h"
#include "display_catalog_presentation.h"
void display_scene_hide_entry_objects(void)
{
 unsigned int i;
 display_fill_background_constant_rectangle(1,9,0,21,14,0);
 display_fill_background_constant_rectangle(0,9,0,21,14,0);
 if(g_display_scene_frame_objects[10])g_display_scene_frame_objects[10]->flags&=~1u;
 for(i=0;i<=3;++i)if(g_display_scene_frame_objects[6+i])g_display_scene_frame_objects[6+i]->flags&=~1u;
}
