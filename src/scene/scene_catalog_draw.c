#include "frame.h"
#include "display_catalog_text.h"
#include "scene_catalog_items.h"
static __inline struct SceneCatalogSlot *catalog_page_slot(const void *slot_field,unsigned int selector,unsigned int first) {
 unsigned int address=(unsigned int)slot_field;
 unsigned int page_offset=selector*sizeof(struct SceneCatalogPage);
 page_offset+=address;
 {register unsigned int offset asm("r1")=first*sizeof(struct SceneCatalogSlot);
  return (struct SceneCatalogSlot *)((unsigned int)*(struct SceneCatalogSlot **)page_offset+offset);}
}
void scene_catalog_draw(unsigned int first,unsigned int second) {
 int i;
 struct FrameObject **object_slot;
 struct SceneCatalogContext *context;
 struct SceneCatalogState *state;
 const void * slot_field;
 unsigned int first_offset;
 if(g_scene_catalog_state.selector==4)return;
 i=7;
 state=&g_scene_catalog_state;
 context=&g_scene_catalog_context;
 slot_field=&context->pages[0].slots;
 first_offset=first*4;
 {unsigned int address=(unsigned int)g_display_scene_frame_objects;
  unsigned int offset=(i+2)*sizeof(*object_slot);offset+=address;object_slot=(struct FrameObject **)offset;}
 for(;i>=0;object_slot--,i--) {
  unsigned int row=i,id;
  struct SceneCatalogSlot *slots;
  if(state->selector!=4) {
   if((unsigned int)i<=3)slots=(struct SceneCatalogSlot *)((unsigned char *)context->record->slots+first_offset);
   else {row=i-4;slots=catalog_page_slot(slot_field,state->selector,second);}
  } else {
   if((unsigned int)i<=4)slots=(struct SceneCatalogSlot *)((unsigned char *)context->record->slots+first_offset);
   else {row=i-5;slots=catalog_page_slot(slot_field,state->selector,second);}
  }
  slots+=row;
  if(slots->kind!=255) {
   id=g_display_scene_catalog[slots->kind].id;
   if(id!=317) {
    (*object_slot)->unknown_0a=id;
    display_scene_refresh_item(*object_slot);
    (*object_slot)->flags|=1;
    frame_set_variant_state(*object_slot,58);
    continue;
   }
  }
  (*object_slot)->flags&=~1U;
 }
}
asm(".align 2,0");
