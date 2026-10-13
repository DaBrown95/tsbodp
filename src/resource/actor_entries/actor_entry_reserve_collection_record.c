#include "resource_actor_entries.h"

struct ActorEntryCollectionRecord *actor_entry_reserve_collection_record(
 struct ActorEntryContext *context,unsigned int group)
{
 struct ActorEntryCollection **reference=&context->collection;
 struct ActorEntryCollection *collection=*reference;
 unsigned int start,index;
 struct ActorEntryCollectionRecord *result;
 if(collection->count>159)return 0;
 start=collection->groups[group].start+collection->groups[group].count;
 result=&collection->records[start];
 {
  unsigned int group_offset;
  unsigned int next;
  index=collection->count;
  group_offset=group*4;
  next=group+1;
  if(index>start) {
   struct ActorEntryCollection **copy_reference=reference;
   do {
    (*copy_reference)->records[index]=(*copy_reference)->records[index-1];
    index--;
   } while(index>start);
  }
  for(next=group+1;next<=49;next++)context->collection->groups[next].start++;
  (*(&context->collection->groups[0].count+group_offset))++;
  context->collection->count++;
  return result;
 }
}
asm(".align 2, 0");
