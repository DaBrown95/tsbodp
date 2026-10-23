#ifndef ACTOR_ENTRY_COLLECTION_H
#define ACTOR_ENTRY_COLLECTION_H
#include "resource_condition_entries.h"

struct ActorEntryCollectionRecord {
 struct ConditionActorEntry entry;
 unsigned int unknown04, unknown08;
};
struct ActorEntryCollectionGroup {
 unsigned char start, count, flags, unknown03;
};
struct ActorEntryCollection {
 unsigned short count, unknown02;
 struct ActorEntryCollectionRecord records[160];
 struct ActorEntryCollectionGroup groups[50];
};
#endif
