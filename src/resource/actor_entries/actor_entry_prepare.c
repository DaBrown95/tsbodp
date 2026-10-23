#include "resource_actor_entries.h"
void actor_entry_prepare(struct ActorEntryContext *context) {
 unsigned int group;
 if(!g_actor_entry_buffer)g_actor_entry_buffer=heap_allocate(0x84c);
 *(void **)((unsigned char*)context+0x31c)=g_actor_entry_buffer;
 {unsigned int offset=0;
 for(group=0;group<=14;++group) {struct ConditionActorEntries *list=&context->lists[group];list->count=0;list->capacity=g_condition_actor_definitions[group].capacity;list->entries=context->storage+offset;offset+=list->capacity;}
 }
 context->active=&context->lists[13];context->secondary=&context->lists[14];
}
asm(".align 2, 0");
