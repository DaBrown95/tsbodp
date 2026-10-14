#include "resource_actor_entries.h"
#include "resource_actor_selection.h"
#include "save_world_scene_selection.h"

unsigned char resource_selection_has_kind_0804573c(void)
{
    unsigned int scene = 15;
    struct ActorEntryCollection **field_root =
        &((struct ActorEntryContext *)g_scene_entry_data)->collection;

    for (; scene <= 49; scene++) {
        if ((unsigned char)save_world_scene_in_selected_row(scene, 0)) {
            struct ActorEntryCollectionGroup *group =
                &(*field_root)->groups[scene];
            register unsigned int index asm("r4") = 0;
            unsigned int count = group->count;

            if (index < count) {
                struct ActorEntryCollection **record_root =
                    &((struct ActorEntryContext *)g_scene_entry_data)->collection;
                struct ActorEntryCollection *collection = *record_root;
                unsigned int start = group->start;
                unsigned char *record = (unsigned char *)(
                    start * sizeof(struct ActorEntryCollectionRecord)
                    + (unsigned int)collection);

                do {
                    if (record[(unsigned int)&((struct ActorEntryCollection *)0)
                               ->records[0].entry.kind]==48)
                        return 1;
                    record += sizeof(struct ActorEntryCollectionRecord);
                    index++;
                } while (index < count);
            }
        }
    }
    return 0;
}
