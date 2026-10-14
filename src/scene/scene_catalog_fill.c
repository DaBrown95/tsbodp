#include "display_catalog_presentation.h"
#include "display_scene_setup.h"
#include "display_catalog_text.h"
#include "display_text_fields.h"
#include "display_text_runtime.h"
#include "display_text_helpers.h"
#include "scene_catalog_content.h"
void scene_catalog_fill(unsigned int first,unsigned int second) {
 unsigned int row,tile,i,number;
 unsigned char *quantities;
 int width=0;
 struct SceneCatalogSlot *slot,*slots,*price_slot;
 char text[32];
 display_fill_background_constant_rectangle(0,2,11,26,8,0);
 row=g_scene_request.scene;
 if(g_scene_catalog_state.selector!=4) {
  if(row<=3) slots=g_scene_catalog_content.catalog->slots+first;
  else {row-=4; slots=g_scene_catalog_content.pages[g_scene_catalog_state.selector].slots+second;}
 } else {
  if(row<=4)slots=g_scene_catalog_content.catalog->slots+first;
  else {row-=5;slots=g_scene_catalog_content.pages[g_scene_catalog_state.selector].slots+second;}
 }
 slot=&slots[row];
 price_slot=slot;
 if(g_scene_catalog_state.selector==4&&g_scene_request.scene<g_scene_catalog_action_row)goto detail_done;
 if(slot->kind==255)goto detail_done;
 display_text_select_font(3,0,-1);
 display_text_set_line_height(12);
 width=display_catalog_draw_name(71,16,88,slot->kind,-1,0);
 display_text_select_font(1,0,-1);
 display_catalog_draw_details(131,16,100,208,slot->kind,-1,0);
 if(slot->kind==255||g_scene_catalog_state.selector==13)goto detail_done;
 display_text_select_font(3,0,-1);
 if(g_scene_request.scene<=3)number=scene_catalog_basic_value(slot->kind);
 else number=scene_catalog_page_value(price_slot->kind);
 display_text_number_field_zero(number);
 display_text_draw_line(531,width+26,88,display_scene_lookup_text(0x184d),0);
 detail_done:
 if(g_scene_catalog_state.selector==4) {
  display_text_select_font(1,0,0);
  tile=571;
  display_fill_background_constant_rectangle(0,0,8,15,1,0);
  for(i=0,quantities=g_scene_catalog_quantities;i<=4;i++) {
   unsigned int byte_address=i;
   byte_address+=(unsigned int)quantities;
   display_text_number_field_zero(*(const unsigned char *)byte_address);
   tile=display_text_draw_line(tile,g_scene_catalog_caption_positions[i].x,g_scene_catalog_caption_positions[i].y,display_scene_lookup_text(0x184e),1);
  }
  if(g_scene_request.scene<g_scene_catalog_action_row) {
   display_text_copy_string(text,display_scene_lookup_text(g_scene_request.scene+504));
   display_text_append_string(text,g_scene_catalog_caption_suffix);
   display_text_number_field_zero(g_scene_catalog_world.values[g_scene_request.scene]);
   display_append_text_resource(text,37);
   display_text_select_font(3,0,-1);
   display_text_draw_line(71,16,88,text,0);
   display_text_select_font(1,0,-1);
   display_text_draw_all_lines(131,16,100,208,display_scene_lookup_text(g_scene_request.scene+795),0);
  }
 }
}
asm(".align 2,0");
