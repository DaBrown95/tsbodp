#include "display_menu_primary.h"
#include "frame.h"
void display_menu_populate_primary_rows(void) {
 unsigned int candidate,mask,row;
 {
 struct DisplayMenuState *menu=&g_display_menu_state;
 candidate=frame_actor_indicator_kind((unsigned char)menu->definition);
 if(menu->unknown_26!=candidate && candidate!=255 && menu->unknown_27!=candidate) {
  if(menu->choice==255) {
   menu->record_group=menu->definition;
   menu->unknown_27=menu->unknown_26;
   menu->unknown_26=candidate;
   menu->choice=g_display_menu_indicator_choices[menu->unknown_26];
  }
  goto needs;
 }
 }
 { struct DisplayMenuState *menu=&g_display_menu_state;
  candidate=display_menu_fallback_indicator((unsigned char)menu->definition);
  if(menu->unknown_26!=candidate && candidate!=255 && menu->unknown_27!=candidate && menu->choice==255) {
   menu->record_group=24;
   menu->unknown_27=menu->unknown_26;
   menu->unknown_26=candidate;
   menu->choice=g_display_menu_indicator_choices[menu->unknown_26];
  }
 }
needs:
 mask=frame_low_need_mask((struct FrameActorNeedState *)g_frame_actor_local_need_state,255);
 if((mask&255)!=0 && mask!=8) {
  row=0;
  do {
   if(row!=3 && (mask&(1<<row)))goto found;
   ++row;
  }while(row<=7);
  goto flags;
found:
  {
   g_display_menu_state.codes[0]=27;
   g_display_menu_state.parameters[0]=g_display_menu_need_parameters[row];
   g_display_menu_state.codes[1]=29;g_display_menu_state.codes[2]=29;g_display_menu_state.codes[3]=29;g_display_menu_state.codes[4]=29;
   g_display_menu_state.parameters[1]=0;g_display_menu_state.parameters[2]=0;g_display_menu_state.parameters[3]=0;g_display_menu_state.parameters[4]=0;
  }
 }else {
  for(row=0;row<=4;++row) {
   g_display_menu_state.codes[row]=display_menu_primary_row_code(row);
   g_display_menu_state.parameters[row]=display_menu_primary_row_parameter(row);
  }
 }
flags:
 if(g_display_menu_state.codes[1]==29)g_display_menu_objects.second->flags&=~1;
 else g_display_menu_objects.second->flags|=1;
 g_display_menu_objects.first->flags&=~1;
}
asm(".align 2, 0");
