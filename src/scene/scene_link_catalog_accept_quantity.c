#include "scene_link_catalog.h"
void scene_link_catalog_accept_quantity(void)
{
 unsigned int count=(unsigned int)g_scene_link_catalog_world.context;
 register struct ConditionActorEntry *entries asm("r12")=((struct ConditionActorEntries *)count)->entries;
 unsigned char selected=entries[g_scene_request.scene-5].kind;
 unsigned int mask_index=g_scene_request.scene-5;
 register unsigned int mask asm("r4")=1u<<mask_index;
 unsigned int remaining=g_scene_request.parameter-1;
 unsigned int index=0;
 if(remaining)count=((struct ConditionActorEntries *)count)->capacity;
 if(remaining && index<count){
  register unsigned int excluded_index asm("r8")=mask_index;
  struct ConditionActorEntry *loop_base=entries;
  for(;remaining && index<count;index++){
   if(index!=excluded_index){
    unsigned char item=loop_base[index].kind;
    if(selected==item || ((unsigned char)(item-119)<=4 && selected>118 && selected<=123)){
     mask|=1u<<index;
     remaining--;
    }
   }
  }
 }
 resource_submit_scene(15,1,mask);
}
asm(".align 2,0");
