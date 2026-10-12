#include "resource_actor_entries.h"
unsigned int actor_entry_add(struct ConditionActorEntries *list,unsigned int kind,unsigned char value1,unsigned char value2) {
 unsigned int success=0,index;
 if(list==&g_actor_entry_alias_list && kind-125<=1)kind=169;
 for(index=0;index<list->capacity;++index) {if(list->entries[index].kind==255) {list->entries[index].kind=kind;list->entries[index].value1=value1;list->entries[index].value2=value2;list->count++;actor_entry_mark_seen(g_actor_entry_seen_words,kind);success=1;break;}}
 { unsigned int game=(unsigned int)&g_resource_game_state;
 if(list==*(struct ConditionActorEntries **)(game+0xf0) && success) {
  if(kind==109)resource_set_triple(1,1,1);
  else if(kind==134)resource_set_triple(2,0,2);
  else if(kind==124)resource_set_triple(2,0,3);
  else if(kind==127)resource_set_triple(2,4,0);
  else if(kind==118)resource_set_triple(2,4,1);
  else if(kind==141)resource_set_triple(4,3,0);
  else if(kind-119<=4) {unsigned int count=*(unsigned char*)(game+0xe6);for(index=0;index<list->capacity;++index)if((unsigned char)(list->entries[index].kind-119)<=4)count++;if(count>2)resource_set_triple(2,2,1);}
  else if(kind==145)resource_set_triple(4,4,1);
  else if(kind-195<=5) {unsigned int value=kind+61;*(unsigned char*)(game+0x43d)=value;*(unsigned char*)(game+0x43e)=1;}
  else if(kind==126)resource_set_triple(3,4,0);
 }
 }
 return success;
}
