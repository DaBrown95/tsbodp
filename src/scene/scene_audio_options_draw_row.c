#include "frame.h"
#include "scene_audio_options.h"
void scene_audio_options_draw_row(unsigned int row) {
 unsigned int tile=row*100+1;
 int x=120,y;
 const char *text;
 char number[32];
 if(row<=1)x=96;
 y=(row<<4)+83;
 text=display_scene_lookup_text(row+18);
 {unsigned int selected=g_scene_request.parameter;int color=0;if(row==selected)color=3;display_text_select_font(3,color,0);}
 {register unsigned int center_style asm("r0")=1;tile=display_text_draw_line(tile,x,y,text,center_style);}
 if(row<=1) {
  x+=80;
  switch(row) {
  case 1:
   if(g_scene_audio_option_levels[1]==10){text=display_scene_lookup_text(209);g_display_scene_frame_objects[4]->flags&=~1U;}
   else if(g_scene_audio_option_levels[1]==0){text=display_scene_lookup_text(207);g_display_scene_frame_objects[3]->flags&=~1U;}
   else {text=display_text_format_number(g_scene_audio_option_levels[1],number);g_display_scene_frame_objects[4]->flags|=1;g_display_scene_frame_objects[3]->flags|=1;}
   break;
  case 0:
   if(g_scene_audio_option_levels[0]==10){text=display_scene_lookup_text(209);g_display_scene_frame_objects[2]->flags&=~1U;}
   else if(g_scene_audio_option_levels[0]==0){text=display_scene_lookup_text(207);g_display_scene_frame_objects[1]->flags&=~1U;}
   else {text=display_text_format_number(g_scene_audio_option_levels[0],number);g_display_scene_frame_objects[2]->flags|=1;g_display_scene_frame_objects[1]->flags|=1;}
   break;
  default:text=0;
  }
  if(text){display_fill_background_constant_rectangle(0,20,y/8,10,2,0);display_text_draw_line(tile,x,y,text,1);}
 }
}
asm(".align 2,0");
