#include "frame.h"
#include "scene_catalog_transfer.h"
void scene_catalog_option(void) {
 unsigned int ordinal=g_scene_request.scene+g_scene_catalog_state.page_start;
 struct ConditionActorEntries *record=g_scene_catalog_transfer_world.record,*destination;
 struct ConditionActorEntry *entry=&record->entries[ordinal];
 if(entry->kind==255)return;
 if(entry->kind==63 && g_scene_catalog_state.selector==0)resource_set_triple(1,1,0);
 if(g_scene_catalog_state.selector==5) {
  if((unsigned char)(entry->kind+61)<=5)
   g_scene_catalog_transfer_world.available=0;
  else {scene_catalog_notice(295);return;}
 } else if(g_scene_catalog_state.selector!=13 && !scene_catalog_basic_value(entry->kind)) {
  scene_catalog_notice(295);return;
 }
 if(g_scene_catalog_state.selector<=12) {
  if(entry->kind==125)
   display_menu_adjust_relation((struct DisplayMenuRelationState *)((unsigned char *)&g_scene_catalog_transfer_world+0x10),12,-3);
  frame_add_game_value(scene_catalog_basic_value(entry->kind));
  scene_catalog_build();
  audio_play_animation_cue(5);
  destination=&g_scene_catalog_transfer_world.lists[g_scene_catalog_state.selector];
 } else {audio_play_animation_cue(1);destination=&g_scene_catalog_transfer_world.lists[13];}
 if(destination->count<destination->capacity) {
  actor_entry_add(destination,entry->kind,entry->value1,entry->value2);
  g_scene_catalog_state.value++;
 }
 condition_update_actor(record,ordinal,1);
 g_scene_catalog_state.count--;
 if(!scene_catalog_has_next(g_scene_catalog_state.page_start,g_scene_catalog_state.count))
  g_display_scene_frame_objects[12]->flags&=~1U;
 if(scene_catalog_has_next(g_scene_catalog_state.row,g_scene_catalog_state.value))
  g_display_scene_frame_objects[14]->flags|=1;
}
asm(".align 2,0");
