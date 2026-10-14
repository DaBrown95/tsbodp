#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
void scene_contact_activity_three_refresh_value(unsigned int selector_arg,unsigned int selected_arg) {
 unsigned char selector=selector_arg,selected=selected_arg;
 unsigned int color=3,tile;int y;char buffer[16],*text;unsigned int amount;
 if(selector==selected)color=6;
 display_text_select_font(3,color,-1);
 tile=selector*4+43;y=selector*16+114;
 {
  int row=y/8;
  display_clear_background_rectangle(0,4,row,2,2);
 }
 if(selector==2)amount=STATE->values[2];else if(selector==1)amount=STATE->values[1];else amount=STATE->values[0];
 text=display_text_format_number(amount,buffer);
 if(text)display_text_draw_line(tile,32,y,text,0);
}
asm(".align 2,0");
