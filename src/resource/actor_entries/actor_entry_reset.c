#include "resource_actor_entries.h"
void actor_entry_reset(struct ActorEntryContext *context) {
 unsigned int group;
 for(group=0;group<=14;++group) {struct ConditionActorEntries *list=&context->lists[group];unsigned int i;for(i=0;i<list->capacity;++i)list->entries[i].kind|=0xff;list->count=0;}
 actor_entry_reset_values(context);
 heap_clear(*(void **)((unsigned char*)context+0x31c),0,0x84c);
 actor_entry_empty_hook((unsigned char*)context+0x320);
 {register unsigned int base asm("r0")=(unsigned int)&g_resource_game_state; actor_entry_add(*(struct ConditionActorEntries **)(base+0xf0),142,0,0);}
}
