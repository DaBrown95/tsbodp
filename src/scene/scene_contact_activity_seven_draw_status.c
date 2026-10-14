#include "scene_contact_activity_seven.h"
void scene_contact_activity_seven_draw_status(void) {
 char number[16];const char *text;
 display_text_select_font(3,3,-1);
 display_clear_background_rectangle(0,1,14,4,2);
 text=display_text_format_number(g_scene_contact_activity_seven_options[STATE->option].rounds[STATE->round].label,number);
 display_text_copy_field_zero(text);
 text=display_scene_lookup_text(0x188e);
 if(text)display_text_draw_line(43,8,112,text,0);
}
