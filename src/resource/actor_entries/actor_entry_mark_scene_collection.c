#include "resource_actor_entries.h"
#include "frame_scene_restore.h"
void actor_entry_mark_scene_collection(struct ActorEntryContext *context,unsigned int scene){struct ActorEntryCollectionGroup *group=(struct ActorEntryCollectionGroup *)&context->collection->groups[scene]; group->flags|=1;}
asm(".align 2,0");
