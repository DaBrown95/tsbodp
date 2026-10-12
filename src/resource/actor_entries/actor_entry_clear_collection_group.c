#include "resource_actor_entries.h"

void actor_entry_clear_collection_group(struct ActorEntryContext *context,
                                        unsigned int group)
{
    struct ActorEntryCollection **reference = &context->collection;
    struct ActorEntryCollectionGroup *range = &(*reference)->groups[group];
    if (range->count) {
        struct ActorEntryCollectionRecord *first =
            &(*reference)->records[range->start];
        unsigned int removed = range->count;
        unsigned int remaining = (*reference)->count - range->start - removed;
        unsigned int index;
        if (remaining)
            heap_copy(first, first + removed, remaining * 12);
        heap_clear(first + remaining, 0, removed * 12);
        {
            index = group + 1;
            if (index <= 49) {
                struct ActorEntryCollection **later = reference;
                do {
                    (*later)->groups[index].start -= removed;
                    index++;
                } while (index <= 49);
            }
        }
        context->collection->count -= removed;
        range->count = 0;
    }
}
asm(".align 2, 0");
