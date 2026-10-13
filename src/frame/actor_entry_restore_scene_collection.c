#include "resource_actor_entries.h"
#include "frame_scene_restore.h"
void actor_entry_restore_scene_collection(struct ActorEntryContext *context,unsigned int scene) {
 struct ActorEntryCollectionGroup *group=&context->collection->groups[scene];
 unsigned int index;
 for(index=0;index<group->count;index++)actor_entry_restore_collection_effect(&context->collection->records[group->start+index]);
 actor_entry_clear_collection_group(context,scene);
}
asm(".align 2,0");
