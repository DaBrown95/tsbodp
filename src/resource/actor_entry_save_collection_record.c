#include "resource_actor_entries.h"
#include "resource_need_effect_collection.h"

void actor_entry_save_collection_record(
    struct ActorEntryContext *context, unsigned int group,
    const struct ActorEntrySavedRecordBytes *record)
{
    struct ActorEntrySavedRecordBytes *destination =
        (struct ActorEntrySavedRecordBytes *)
        actor_entry_reserve_collection_record(context, group);
    if (destination)
        *destination = *record;
}
