#include "display_menu_choice_restore.h"
void display_menu_restore_choice(void)
{
 const struct DisplayMenuChoiceRecord *record;
 unsigned int complete;
 unsigned int i;
 record=(const struct DisplayMenuChoiceRecord *)g_display_menu_text_records[g_display_menu_state.record_group];
 record+=g_display_menu_state.choice;
 if(record->flags) {
  /* Normalize the observed flag mask to the completion word. */
  complete=(0u-(record->flags&2))>>31;
  if(record->flags&0x200) {((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->balance-=200;resource_set_triple(2,1,2);}
  if(record->flags&0x400) {((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->balance-=1000;resource_set_triple(2,3,2);}
  if(record->flags&0x1000) {((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->balance-=500;resource_set_triple(1,5,2);}
  if(record->flags&0x800) {((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->balance-=2500;resource_set_triple(3,3,2);}
  if(record->flags&0x2000) {((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->balance-=3000;resource_set_triple(2,5,1);}
  if(record->flags&0x4000) {
   ((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->balance-=10000;
   if(((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->kind==3)resource_set_triple(3,5,1);
   else if(((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->kind==4)resource_set_triple(4,2,0);
  }
  if(record->flags&4)display_menu_apply_delta(1);
  if(record->flags&8)display_menu_apply_delta(-1);
  if(record->flags&16)display_menu_apply_delta(3);
  if(record->flags&32)display_menu_apply_delta(-3);
  if(record->flags&64)display_menu_apply_delta(5);
  if(record->flags&128)display_menu_apply_delta(-5);
  if(record->flags&0x100) {
   transition_object_set_state((struct FrameObject *)g_scene_primary_views.slots[0].object,0);
   frame_set_variant_state(g_scene_primary_views.slots[0].object->indicator,64);
  }
  {
   unsigned int entry=255;
   if(record->flags&0x8000)entry=127;
   if(record->flags&0x10000)entry=frame_random_range(119,123);
   if(entry!=255) {
    if(!(unsigned char)actor_entry_add(((struct DisplayMenuChoiceWorld *)&g_save_world_init_state)->list,entry,0,0)) {
     g_save_world_transition_rows[g_scene_primary_views.current_view].flags|=0x200000;
     complete=0;
     resource_submit_scene(1,2,(unsigned int)g_display_menu_notice_owner);
    }
   }
  }
  if(record->flags&0x20000) {actor_entry_add(&g_display_menu_restore_extra_entries,99,0,0);condition_activate_entry(2,2,4);}
  if(record->flags&0x80000)resource_set_triple(1,0,1);
  if(record->flags&0x40000)resource_set_triple(3,2,0);
  if(record->flags&0x1000000)resource_set_triple(4,0,0);
  if(record->flags&0x8000000)resource_set_triple(4,1,1);
  if(record->flags&0x4000000)resource_set_triple(4,2,2);
  if(record->flags&0x2000000)resource_set_triple(4,3,1);
  if(record->flags&0x10000000)resource_set_triple(4,4,0);
  if(record->flags&0x100000)resource_set_triple(4,4,2);
  if(record->flags&0x400000)resource_set_triple(1,5,0);
  if(record->flags&0x200000)resource_set_triple(3,0,3);
  if(record->flags&0x800000)resource_set_triple(2,3,0);
  if(record->flags&0x80000000) {resource_submit_scene(1,2,(unsigned int)g_display_menu_notice_owner);audio_play_animation_cue(80);}
  if(complete) {
   unsigned int code;
   if(g_display_menu_state.unknown_26==85)frame_add_game_value(1000);
   code=((struct DisplayMenuChoiceSelection *)&g_display_menu_state)->codes&0x00ffff00;
   if(code==0x006f0500||code==0x00730f00)condition_finish_display_kind(108);
   else if(code==0x00700900||code==0x00741100)condition_finish_display_kind(109);
   else if(g_display_menu_state.unknown_26==118)condition_finish_display_kind(117);
   else condition_finish_display_kind(frame_actor_indicator_kind((unsigned char)g_display_menu_state.record_group));
  }
 }
 for(i=0;i<=4;++i)if(record->kinds[i]!=255)resource_set_display_kind(record->kinds[i]);
 if(record->row!=255) {
  if(record->column!=255) {
   for(i=0;i<=4;++i)if(record->entries[i]!=255)condition_activate_entry(record->row,record->column,record->entries[i]);
  } else {condition_select_row(record->row);g_display_scene_request_state.unknown_10=3;}
 }
 if(record->reset==255)g_display_menu_state.choice=255;
}
asm(".align 2, 0");
