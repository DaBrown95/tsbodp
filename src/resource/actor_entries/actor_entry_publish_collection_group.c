#include "resource_actor_entries.h"

void actor_entry_publish_collection_group(struct ActorEntryContext *context,
                                          unsigned int group)
{
    struct ActorEntryCollection **reference = &context->collection;
    unsigned int offset = group * 4 + 0x784;
    struct ActorEntryCollection *collection = *reference;
    struct ActorEntryCollectionGroup *range =
        (void *)((unsigned int)collection + offset);
    struct ActorEntryCollectionRecord *record = &collection->records[range->start];
    unsigned int left = range->count;
    if (left) {
        do {
            unsigned int kind = record->entry.kind;
            struct ConditionActorEntries *list = context->active;
            int space = 0;
            if (list->count < list->capacity)
                space = 1;
            if (space) {
                if (g_display_scene_catalog[kind].category != 6)
                    actor_entry_add(list, kind, record->entry.value1,
                                    record->entry.value2);
                record++;
                left--;
            } else
                break;
        } while (left);
    }
    {
        unsigned char *game = (unsigned char *)&g_resource_game_state;
        unsigned char *timer = game + 0x43c;
        if (*timer != 50) {
            struct ConditionActorEntries *list = context->active;
            int space = 0;
            if (list->count < list->capacity)
                space = 1;
            if (space) {
                *timer = 50;
                actor_entry_add(list, game[0x43d] + 195, 0, 0);
            } else {
                game[0x43e] = 0;
                *timer = 50;
            }
        }
    }
    actor_entry_clear_collection_group(context, group);
}
asm(".align 2, 0");
