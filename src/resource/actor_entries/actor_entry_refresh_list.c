#include "resource_actor_entries.h"

static inline unsigned int cleanup_kind(const struct ConditionActorEntry *entry)
{
 register unsigned int kind asm("r1")=entry->kind;
 register unsigned char result asm("r0")=kind;
 return result;
}

void actor_entry_refresh_list(struct ActorEntryContext *context,unsigned int group)
{
 struct ConditionActorEntries *list=&context->lists[group];
 struct ConditionActorDefinition *definition=&g_condition_actor_definitions[group];
 unsigned int index;
 if(list->count>definition->retained) {
  index=definition->retained;
  if(index<definition->capacity) {
   unsigned char zero=0;
   unsigned int offset=index*4;
   do {
    register struct ConditionActorEntry *array asm("r0")=list->entries;
    register struct ConditionActorEntry *entry asm("r4")=(void*)((unsigned int)array+offset);
    if(cleanup_kind(entry)!=255) {
     entry->kind=255;
     ((unsigned char*)list->entries)[offset+1]=zero;
     ((unsigned char*)list->entries)[offset+2]=zero;
     list->count--;
    }
    offset+=4;
    index++;
   } while(index<definition->capacity);
  }
 }
 {
  index=list->count;
  if(index<definition->count) {
   unsigned int game=(unsigned int)&g_resource_game_state;
   do {
    struct ConditionActorEntry *destination=&list->entries[index];
    const struct ActorEntrySeed *seed=(const struct ActorEntrySeed*)definition->values+index;
    const struct ActorEntrySeed *record=seed;
    switch((int)seed->entry.kind) {
    case 254:destination->kind=actor_entry_choose_base();break;
    case 253:destination->kind=actor_entry_choose_195();break;
    case 252:destination->kind=actor_entry_choose_201();break;
    case 251:destination->kind=actor_entry_choose_209();break;
    default:
     {
      if((*(unsigned int*)&record->row&0xffffff)==0x50605)
       *destination=seed->entry;
      else {
       unsigned int offset=record->index*4;
       unsigned char *state;
       offset+=record->column*24;
       offset+=record->row*144;
       state=(void*)(offset+game);
       if(state[0x448]&&!state[0x449])
        *destination=seed->entry;
       else {
        switch((int)definition->fallback) {
        case 254:destination->kind=actor_entry_choose_base();break;
        case 253:destination->kind=actor_entry_choose_195();break;
        case 252:destination->kind=actor_entry_choose_201();break;
        case 251:destination->kind=actor_entry_choose_209();break;
        }
       }
      }
     }
    }
    destination->value1=0;
    destination->value2=0;
    list->count++;
    index++;
   } while(index<definition->count);
  }
 }
}
