#include "scene_catalog_confirm.h"

static inline struct ConditionActorEntry *catalog_entry_prefix(
    struct ConditionActorEntries *list, unsigned int ordinal,
    unsigned int *kind_output)
{
    register struct CatalogWordOwner entry_words asm("r4");
    register unsigned int ordinal_offset asm("r1");
    register struct ConditionActorEntries *list_reader asm("r4");
    entry_words.low = ordinal;
    ordinal_offset = entry_words.low << 2;
    list_reader = list;
    entry_words.low = (unsigned int)list_reader->entries + ordinal_offset;
    entry_words.high = ((struct ConditionActorEntry *)entry_words.low)->kind;
    *kind_output = entry_words.high;
    return (struct ConditionActorEntry *)entry_words.low;
}

void scene_catalog_confirm_original(void)
{
 volatile unsigned int changed=0;
 register int row asm("r1");
 register unsigned int ordinal asm("r8");
 register unsigned int scene_epoch asm("r2");
 register unsigned int first_selector asm("r1");
 unsigned int kind;
 register unsigned int selector_offset asm("r6");
 register struct SceneCatalogState *state_input asm("r0");
 register struct CatalogWordOwner words asm("r1");
 register struct SceneRequest *request_input asm("r0");
 struct SceneRequest *request;
 register struct SceneCatalogState *state asm("r3");
 register struct ConditionActorEntries *list asm("r9");
 struct ConditionActorEntries *record;
 register struct ConditionActorEntries *lists asm("r3");
 struct ConditionActorEntry *entry;
 register union CatalogWorldViews *world asm("ip");
 state_input=&g_scene_catalog_state;
 first_selector=state_input->selector;
 state=state_input;
 if(first_selector!=4) {request_input=&g_scene_request;row=state->row;row-=4;}
 else {request_input=&g_scene_request;row=state->row;row-=5;}
 scene_epoch=request_input->scene;
 scene_epoch+=row;
 ordinal=scene_epoch;
 request=request_input;
 words.high=state->selector;
 selector_offset=words.high<<3;
 lists=&g_catalog_world.entries.lists[0];
 {
  words.low=selector_offset+(unsigned int)lists;
  list=(struct ConditionActorEntries *)words.low;
 }
 entry=catalog_entry_prefix(list,ordinal,&kind);
 world=(union CatalogWorldViews *)((unsigned int)lists-248);
 record=*(struct ConditionActorEntries **)((unsigned int)lists-8);
 if(kind==255)return;
 if(request->mode==1) {
  if(!(unsigned char)actor_entry_is_full(record)) {
   resource_submit_scene(23,0,kind);
   g_scene_queued_request.parameter=(entry->value2<<8)|entry->value1;
   condition_update_actor(list,ordinal,1);
   audio_play_animation_cue(1);
  }
 } else {
  unsigned int selector=words.high;
  if(selector!=13) {
   unsigned int price=(g_display_scene_catalog[kind].number_value*
    ({
     register const struct SceneCatalogValueRate *rate_base asm("r1") =
      g_scene_catalog_value_rates;
     ({
      register unsigned int rate_column asm("r1")=(unsigned int)rate_base+4u;
      *(const unsigned int *)(selector_offset+rate_column);
     });
    }))>>16;
   if(({register union CatalogWorldViews *value_reader asm("r2")=world;value_reader->value.value;})<(int)price)goto insufficient;
  }
  if(kind-195<=5 && ({register unsigned char *availability_reader asm("r0")=(unsigned char *)((unsigned int)lists+838);*availability_reader;})==1 && selector!=13) {
   scene_catalog_notice(297);
   audio_play_animation_cue(2);
   return;
  }
  if(!(unsigned char)frame_actor_has_action(kind)) {
   unsigned int shifted_result=(unsigned int)actor_entry_add(record,kind,entry->value1,entry->value2)<<24;
   if(shifted_result) {
    g_scene_catalog_state.count++;
    if(kind!=129) {
     condition_update_actor(list,ordinal,1);
     g_scene_catalog_state.value--;
    }
    {register unsigned int outcome asm("r2")=1;changed=outcome;}
   } else {
    {register unsigned int failure_status asm("r4")=0;changed=failure_status;}
    scene_catalog_notice(292);
   }
  } else {
   struct FrameObject *object=g_frame_actor_need_input.views[g_frame_actor_need_input.local_player].actor;
   transition_object_set_state(object,19);
   frame_set_variant_state(object,0);
   ((struct FrameActorActionWork *)object)->action=kind;
   if(kind==170)((struct FrameActorActionWork *)object )->variation.word=frame_random_bounded(7);
   else if(kind>208) {
    condition_update_actor(list,ordinal,1);
    g_scene_catalog_state.value--;
   }
   resource_submit_scene(1,2,g_frame_world_id);
   changed=1;
  }
 }
 goto completed;
 insufficient:
 scene_catalog_notice(293);
 completed:
 if(({register unsigned int completed_status asm("r1")=changed;completed_status;})==1) {
  if(scene_catalog_has_next(g_scene_catalog_state.page_start,g_scene_catalog_state.count)) {
   struct FrameObject *arrow_receiver=g_display_scene_frame_objects[12];
   unsigned int old_flags=arrow_receiver->flags;
   register unsigned int arrow_status asm("r2")=changed;
   arrow_receiver->flags=old_flags|arrow_status;
  }
  if(!scene_catalog_has_next(g_scene_catalog_state.row,g_scene_catalog_state.value))g_display_scene_frame_objects[14]->flags&=~1U;
  if(g_scene_catalog_state.selector!=13) {
   unsigned int price=(g_display_scene_catalog[kind].number_value*g_scene_catalog_value_rates[g_scene_catalog_state.selector].page)>>16;
   frame_add_game_value(-(int)price);
   scene_catalog_build();
   audio_play_animation_cue(5);
  } else audio_play_animation_cue(1);
  if(kind==99) {
   resource_set_triple(2,2,4);
   resource_set_triple(3,2,3);
  }
 }
}
asm(".align 2, 0");
