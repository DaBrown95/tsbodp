#include "resource_actor_entries.h"
#include "resource_collection_selection.h"

void condition_select_actor(void *base, unsigned int row)
{
    struct ActorEntryContext *context = (struct ActorEntryContext *)base;

    switch (row) {
    case 0:
    case 1:
        break;
    case 2:
        actor_entry_publish_collection_group(context, 16);
        actor_entry_publish_collection_group(context, 17);
        break;
    case 3:
        actor_entry_publish_collection_group(context, 24);
        actor_entry_publish_collection_group(context, 25);
        actor_entry_publish_collection_group(context, 23);
        break;
    case 4:
        actor_entry_publish_collection_group(context, 46);
        actor_entry_publish_collection_group(context, 48);
        actor_entry_publish_collection_group(context, 47);
        break;
    default:
        break;
    }
}
