#include "frame.h"
#include "scene_catalog_text.h"
void scene_catalog_quantity(void) {
 char text[12];
 if(g_scene_request.parameter==1)g_display_scene_frame_objects[12]->flags&=~1U;
 else g_display_scene_frame_objects[12]->flags|=1;
 if(g_scene_request.parameter==g_scene_catalog_world.quantities[g_scene_request.scene])
  g_display_scene_frame_objects[11]->flags&=~1U;
 else g_display_scene_frame_objects[11]->flags|=1;
 display_fill_background_constant_rectangle(1,13,10,4,2,0x918c);
 display_text_format_number(g_scene_request.parameter,text);
 display_text_draw_line(521,120,80,text,1);
}
asm(".align 2,0");
