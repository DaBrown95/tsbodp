#include "resource_actor_entries.h"
#include "resource_actor_selection.h"
int resource_count_selectable_actor_entries(void) {
 int groups[3],total;unsigned int group_index;
 resource_selection_group_ids_08045794(groups);
 total=0;group_index=0;
 if(groups[0]!=-1){
  register struct ActorEntryCollection *collection=*(struct ActorEntryCollection **)(g_scene_entry_data+(unsigned int)&((struct ActorEntryContext*)0)->collection);
  int *cursor=groups;
  do {
   register unsigned int offset asm("r0")=(unsigned int)*cursor++*sizeof(struct ActorEntryCollectionGroup);
   offset+=(unsigned int)&((struct ActorEntryCollection*)0)->groups;
   {register struct ActorEntryCollectionGroup *group asm("r4")=(struct ActorEntryCollectionGroup *)((unsigned int)collection+offset);
    total+=group->count;}
   group_index++;
  }while(group_index<=2 && *cursor!=-1);
 }
 if(!total)return 0;
 for(group_index=0;group_index<3 && groups[group_index]!=-1;group_index++){
  struct ActorEntryCollection **collection_root=&((struct ActorEntryContext *)g_scene_entry_data)->collection;
  struct ActorEntryCollectionGroup *group=&(*collection_root)->groups[groups[group_index]];
  register unsigned int entry asm("r5")=0;unsigned int next_group=group_index+1;
  if(entry<group->count)do {
   unsigned int kind=((struct ActorEntryContext *)g_scene_entry_data)->collection->records[group->start+entry].entry.kind;
   if(!(unsigned char)resource_selection_kind_available_0804565c(kind))total--;
   entry++;
  }while(entry<group->count);
  group_index=next_group-1;
 }
 return total;
}
