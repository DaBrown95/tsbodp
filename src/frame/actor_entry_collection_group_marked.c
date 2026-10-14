#include "frame_need_effect_factory.h"
#include "resource_actor_entries.h"

unsigned char actor_entry_collection_group_marked(struct ActorEntryContext *context,unsigned int group)
{
 struct ActorEntryCollection **reference=&context->collection;
 unsigned int offset=group*4+0x784;
 struct ActorEntryCollection *collection=*reference;
 struct ActorEntryCollectionGroup *range=(void *)((unsigned int)collection+offset);
 return range->flags&1;
}
asm(".align 2, 0");
