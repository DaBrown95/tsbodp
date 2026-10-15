#include "scene_choice_panel.h"
void scene_choice_panel_initialize(void)
{
 unsigned int width_limit=200,index=0,lines,width,metric,pixels;
 while(index<5 && g_need_effect_choice_text[index]) {
  SCENE_CHOICE_PANEL_COUNT++;
  ++index;
 }
 if(!g_actor_scene_request.active) {
  g_scene_request.scene=((SCENE_CHOICE_PANEL_FLAGS&1) && SCENE_CHOICE_PANEL_COUNT>1) ? 1 : 0;
 }
 if(g_actor_scene_request.active==1 && g_actor_scene_request.object) width_limit=168;
 index=0;
 g_scene_request.parameter=index;
 frame_enable_primary_object_flags(0x02000000U);
 display_text_select_font(3,3,0);
 g_scene_choice_panel_size.width=index;
 lines=0;
 while(index<SCENE_CHOICE_PANEL_COUNT) {
  ++lines;
  width=display_text_measure_width(display_scene_lookup_text(g_need_effect_choice_text[index]));
  if(g_actor_scene_request.object) {
   unsigned int old_width;
   width+=32;
   old_width=g_scene_choice_panel_size.width;
   metric=(width+3)>>3;
   if(metric<old_width) metric=old_width;
   g_scene_choice_panel_size.width=metric;
   g_scene_choice_panel_size.width=g_scene_choice_panel_size.width>25 ? 25 : g_scene_choice_panel_size.width;
   width-=32;
  } else {
   unsigned int old_width;
   old_width=g_scene_choice_panel_size.width;
   metric=(width+3)>>3;
   if(metric<old_width) metric=old_width;
   g_scene_choice_panel_size.width=metric;
   g_scene_choice_panel_size.width=g_scene_choice_panel_size.width>25 ? 25 : g_scene_choice_panel_size.width;
  }
  while(width>width_limit) {width-=width_limit;++lines;}
  ++index;
 }
 g_scene_choice_panel_size.width+=2;
 pixels=lines*12+16;
 g_scene_choice_panel_size.height=pixels>>3;
 if(display_bios_remainder(pixels,8)) ++g_scene_choice_panel_size.height;
 if(lines==1 && g_actor_scene_request.object) g_scene_choice_panel_size.height=5;
 if(g_actor_scene_request.active==1) {
  SCENE_CHOICE_PANEL_X=(30-(int)g_scene_choice_panel_size.width)/2;
  SCENE_CHOICE_PANEL_Y=7-(g_scene_choice_panel_size.height>>1);
  if(g_actor_scene_request.object)
   frame_set_position(g_actor_scene_request.object,(SCENE_CHOICE_PANEL_X<<19)+0x130000,(SCENE_CHOICE_PANEL_Y<<19)+0x140000);
 }
 g_scene_request.unknown_10=0;
}
asm(".align 2,0");
