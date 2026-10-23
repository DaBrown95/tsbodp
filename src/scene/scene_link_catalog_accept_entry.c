#include "scene_link_catalog.h"
void scene_link_catalog_accept_entry(void)
{
 unsigned char *owner_cursor=(unsigned char *)g_scene_link_catalog_world.context;
 struct ConditionActorEntry *entries=((struct ConditionActorEntries *)owner_cursor)->entries;
 unsigned char selected=entries[g_scene_request.scene-5].kind;
 if(selected!=255){
  unsigned int count=1;
  if(selected!=129){
   unsigned int index;
   register unsigned int guard_bound asm("r0");
   count=0;
   index=0;
   guard_bound=((struct ConditionActorEntries *)owner_cursor)->capacity;
   if(index<guard_bound){
    register unsigned int loop_limit asm("r6")=guard_bound;
    owner_cursor=(unsigned char *)entries;
    do{
     unsigned char item=*owner_cursor;
     if(item==selected || ((unsigned char)(item-119)<=4 && selected>118 && selected<=123))count++;
     owner_cursor+=4;
     index++;
    }while(index<loop_limit);
   }
  }
  if(count>1){
   g_scene_request.unknown_10=2;
   g_scene_request.parameter=1;
   display_text_number_field_zero(count);
   scene_link_catalog_draw_panel(0);
   g_scene_link_catalog_quantity_limit=count;
   scene_link_catalog_draw_quantity();
  }else{
   resource_submit_scene(15,1,1u<<(g_scene_request.scene-5));
   audio_play_animation_cue(7);
  }
 }else{
  resource_submit_scene(15,1,0);
  audio_play_animation_cue(2);
 }
}
asm(".align 2,0");
