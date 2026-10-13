#include "display_menu.h"
#include "display_catalog_presentation.h"
#include "display_scene_setup.h"
#include "display_catalog_text.h"
#include "frame_actor_relation.h"
void display_menu_draw_lines(void)
{
 unsigned int remaining=0x7fffffff;
 unsigned int tile=258,row;
 const char *text;
 for(row=0;row<=4;++row)g_display_menu_state.positions[row]=0;
 row=0;
 do {
  unsigned int code;
  unsigned int next, id;
  if(row==g_display_scene_request_state.scene)display_text_select_font(3,3,-1);
  else display_text_select_font(3,0,-1);
  display_text_set_line_height(12);
  code=g_display_menu_state.codes[row];

  if(code!=29) {
   if(code<=21) {
    const unsigned short *base=g_frame_actor_greetings[g_display_menu_state.definition].text_ids;
    unsigned int address=(unsigned int)&g_display_catalog_state;
    unsigned int variant=*(unsigned int *)(address+0x440);
    {
     const unsigned short *entry = base + variant;
     /* A short loaded text ID; no constrained value crosses a call. */
     register unsigned int base_id asm("r0") = *entry;
     id = base_id + g_display_menu_state.parameters[row];
    }
   } else if(code==22)id=0x480;
   else if(code<=26) {
    const struct DisplayMenuTextRecord *records=g_display_menu_text_records[g_display_menu_state.record_group];
    unsigned int entry=records[g_display_menu_state.choice].entries[row];
    id=records[entry].text;
   } else if(code==27) {
    id=g_display_menu_state.parameters[g_display_scene_request_state.scene]+0x482;
   } else if(code==28)id=0x481;
   else goto keep_text;
   text=display_scene_lookup_text(id);
keep_text:
   g_display_menu_state.positions[next=row+1]=g_display_menu_state.positions[row];
   while(*text) {
    tile=display_text_draw(tile,72,g_display_menu_state.positions[next],144,&text,0,&remaining);
    g_display_menu_state.positions[next]+=12;
   }
  }
  row=row+1;
 }while(row<=4);
}
asm(".align 2, 0");
