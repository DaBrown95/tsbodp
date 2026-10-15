#include "scene_record_selection.h"
void scene_record_selection_draw_choice(unsigned int index, unsigned int selected)
{
 unsigned int fill = 0, tile;
 int pixel_y;
 const char *text;
 if (index == selected) fill = 3;
 display_text_select_font(3,fill,0);
 tile = index*20+347;
 pixel_y = (int)(index*24+52);
 text = display_scene_lookup_text(index+210);
 display_text_draw_line(tile,120,pixel_y,text,1);
}
