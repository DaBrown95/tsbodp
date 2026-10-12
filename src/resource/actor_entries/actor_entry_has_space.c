#include "resource_actor_entries.h"
int actor_entry_has_space(struct ConditionActorEntries *list) {int result=0; if(list->count<list->capacity)result=1;return result;}
