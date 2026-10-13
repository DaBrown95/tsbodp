#include "resource_actor_entries.h"

static inline unsigned int actor_entry_collection_count(
    struct ActorEntryCollection **reference)
{
    register struct ActorEntryCollection *collection asm("r0") = *reference;
    return collection->count;
}

void actor_entry_remove_collection_record(struct ActorEntryContext *context,
                                          unsigned int group,
                                          unsigned int selected)
{
    struct ActorEntryCollection **reference = &context->collection;
    unsigned int index = (*reference)->groups[group].start;
    (*reference)->groups[group].count--;
    (*reference)->count--;
    index += selected;
    goto check_record;
    do {
        unsigned int collection = (unsigned int)*reference;
        struct ActorEntryCollectionRecord *destination =
            (void *)(collection + index * 12);
        struct ActorEntryCollectionRecord *source;
        index++;
        source = (void *)(collection + index * 12);
        destination = (void *)((unsigned int)destination + 4);
        source = (void *)((unsigned int)source + 4);
        *destination = *source;
check_record:;
    } while (index < actor_entry_collection_count(reference));
    {
        struct ActorEntryCollection **clear_reference = &context->collection;
        heap_clear(&(*clear_reference)->records[index], 0, 12);
        {
            unsigned int next = group + 1;
            if (next <= 49) {
                struct ActorEntryCollection **later = clear_reference;
                do {
                    (*later)->groups[next].start--;
                    next++;
                } while (next <= 49);
            }
        }
    }
}
asm(".align 2, 0");
