#include "resource_actor_entries.h"
int actor_entry_find_capacity(struct ConditionActorEntries *list,int kind) {
 int index=0; for(;index<list->capacity;++index) {if(list->entries[index].kind==kind)break;}
 if(index==list->capacity)index=-1; return index;
}
