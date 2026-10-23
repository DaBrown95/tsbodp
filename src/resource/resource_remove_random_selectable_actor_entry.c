#include "resource_actor_entries.h"
#include "resource_actor_selection.h"
void resource_remove_random_selectable_actor_entry(void)
{
 int groups[3]; struct ActorEntryCollection **collection_root;
 int *selected; struct ActorEntryCollectionGroup *group;
 unsigned int entry,kind,index;
 resource_selection_group_ids_08045794(groups);
 collection_root=&((struct ActorEntryContext*)g_scene_entry_data)->collection;
choose:
 selected=&groups[frame_random_range(0,(unsigned char)resource_selection_group_count_080456f4()-1)];
 group=&(*collection_root)->groups[*selected];
 if(!group->count)goto choose;
 entry=frame_random_range(0,*(volatile unsigned char *)&group->count-1);
 kind=(*collection_root)->records[group->start+entry].entry.kind;
 if(!(unsigned char)resource_selection_kind_available_0804565c(kind))goto choose;
 {
  register struct ResourceSelectionWorld *world asm("r3")=&g_resource_selection_world;
  kind=world->collection->records[group->start+entry].entry.kind;
  if((unsigned char)(kind+61)<=5){register unsigned char *clear_pointer asm("r1")=&world->unknown43e;*clear_pointer=0;}
 }
 for(index=0;index<group->count;index++) {
  if(index==entry)actor_entry_remove_collection_record((struct ActorEntryContext*)g_scene_entry_data,*selected,index);
 }
}
