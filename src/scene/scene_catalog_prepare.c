#include "frame.h"
#include "display_catalog_text.h"
#include "scene_catalog_objects.h"
static __inline struct SceneCatalogSlot *catalog_prepare_page_slot(const void *field,unsigned int selector,unsigned int row) {
 unsigned int address=(unsigned int)field;
 unsigned int page_offset=selector*sizeof(struct SceneCatalogPage);page_offset+=address;
 {unsigned int offset=row*sizeof(struct SceneCatalogSlot);
 return (struct SceneCatalogSlot *)((unsigned int)*(struct SceneCatalogSlot **)page_offset+offset);}
}
static __inline unsigned int catalog_prepare_descriptor(const struct SceneCatalogSlot *entry) {
 const struct DisplayCatalogItem *catalog=g_display_scene_catalog;
 return catalog[entry->kind].id;
}
void scene_catalog_prepare(void) {
 int i;
 if(g_scene_catalog_state.selector==4) {
  g_display_scene_frame_objects[0]=frame_create_scene_object(123,12,1,1);
  g_display_scene_frame_objects[12]=frame_create_scene_object(68,268,14,1);
  g_display_scene_frame_objects[12]->display_layer=0;
  g_display_scene_frame_objects[12]->flags&=~1U;
  g_display_scene_frame_objects[11]=frame_create_scene_object(67,269,14,1);
  g_display_scene_frame_objects[11]->display_layer=0;
  g_display_scene_frame_objects[11]->flags&=~1U;
 } else {
  g_display_scene_frame_objects[0]=frame_create_scene_object(39,10,1,1);
  g_display_scene_frame_objects[11]=frame_create_scene_object(47,269,14,1);
  g_display_scene_frame_objects[11]->flags&=~1U;
  g_display_scene_frame_objects[12]=frame_create_scene_object(48,268,14,1);
 }
 if(!scene_catalog_has_next(g_scene_catalog_state.page_start,g_scene_catalog_state.count))
  g_display_scene_frame_objects[12]->flags&=~1U;
 g_display_scene_frame_objects[10]=frame_create_scene_object(51,234,15,1);
 g_display_scene_frame_objects[13]=frame_create_scene_object(49,269,14,1);
 g_display_scene_frame_objects[13]->flags&=~1U;
 g_display_scene_frame_objects[14]=frame_create_scene_object(50,268,14,1);
 if(!scene_catalog_has_next(g_scene_catalog_state.row,g_scene_catalog_state.value))
  g_display_scene_frame_objects[14]->flags&=~1U;
 if(g_scene_catalog_state.selector!=4) {
  int object_id,coordinate;unsigned int slot_offset;
  struct SceneCatalogContext *context;
  struct SceneCatalogState *current_state;
  unsigned int page_field_address;
  i=7;
  current_state=&g_scene_catalog_state;
  context=&g_scene_catalog_context;
  page_field_address=(unsigned int)&context->pages[0].slots;
  slot_offset=36;coordinate=9;object_id=46;
  for(;i>=0;slot_offset-=4,coordinate--,object_id--,i--) {

   unsigned int row=i;
   struct SceneCatalogSlot *slots;
  if(current_state->selector!=4) {
   if((unsigned int)i<=3)slots=context->record->slots;
   else {row=i-4;slots=(*(struct SceneCatalogSlot **)(current_state->selector*sizeof(struct SceneCatalogPage)+page_field_address));}
  } else {
   if((unsigned int)i<=4)slots=context->record->slots;
   else {row=i-5;slots=(*(struct SceneCatalogSlot **)(current_state->selector*sizeof(struct SceneCatalogPage)+page_field_address));}
  }
  slots+=row;
   if(slots->kind!=255)(*(struct FrameObject **)((unsigned char *)g_display_scene_frame_objects+slot_offset))=frame_create_scene_object(object_id,catalog_prepare_descriptor(slots),coordinate,1);
   else {
    (*(struct FrameObject **)((unsigned char *)g_display_scene_frame_objects+slot_offset))=frame_create_scene_object(object_id,229,coordinate,1);
    (*(struct FrameObject **)((unsigned char *)g_display_scene_frame_objects+slot_offset))->flags&=~1U;
   }
  }
 } else {
  for(i=0;i<=4;i++) {
   g_display_scene_frame_objects[i+1]=frame_create_scene_object(i+123,i+229,i+2,1);
   frame_set_variant_state(g_display_scene_frame_objects[i+1],11);
  }
  for(i=3;i>=0;i--) {
   struct SceneCatalogSlot *selected=catalog_prepare_page_slot(&g_scene_catalog_context.pages[0].slots,g_scene_catalog_state.selector,i);
   if(selected->kind!=255)g_display_scene_frame_objects[i+2]=frame_create_scene_object(i+43,g_display_scene_catalog[selected->kind].id,i+7,1);
   else {
    g_display_scene_frame_objects[i+6]=frame_create_scene_object(i+43,229,i+7,1);
    g_display_scene_frame_objects[i+6]->flags&=~1U;
   }
  }
  g_display_scene_frame_objects[11]->flags&=~1U;
  g_display_scene_frame_objects[12]->flags&=~1U;
 }
}
