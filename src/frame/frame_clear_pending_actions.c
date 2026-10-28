#include "frame_actor_choices.h"
#include "frame_actor_idle.h"
#include "resource_actor_entries.h"
#include "resource_actor_selection.h"

unsigned char frame_clear_pending_actions(unsigned int category)
{
    register unsigned int choice asm("r4") = category;
    unsigned int result = 0;
    struct FramePendingAction *node = g_frame_pending_action_head;
    unsigned int world;
    unsigned int stored, match;

    while (node) {
        struct FramePendingAction *next = node->next;
        stored = node->category;
        match = 0;

        switch (choice) {
        case 1: if (stored == 2) match = 1; break;
        case 2: if (stored == 1) match = 1; break;
        case 3: if (stored == 3) match = 1; break;
        }
        if (match) {
            node->category = 0;
            node->timer = 0;
            stored = 1;
            result = stored;
        }
        node = next;
    }

    for (world = 0; world < 50; world++) {
        unsigned int count =
            ((struct ActorEntryContext *)g_scene_entry_data)->collection->groups[world].count;
        if (count && frame_world_in_idle_exclusion_set(world)) {
            unsigned int first =
                ((struct ActorEntryContext *)g_scene_entry_data)->collection->groups[world].start;
            unsigned int i;
            for (i = first; i < first + count; i++) {
                stored =
                    ((struct ActorEntryContext *)g_scene_entry_data)->collection->records[i].entry.value1;
                match = 0;

                switch (choice) {
                case 1: if (stored == 2) match = 1; break;
                case 2: if (stored == 1) match = 1; break;
                case 3: if (stored == 3) match = 1; break;
                }
                if (match) {
                    ((struct ActorEntryContext *)g_scene_entry_data)->collection->records[i].entry.value1 = 0;
                    ((struct ActorEntryContext *)g_scene_entry_data)->collection->records[i].entry.value2 = 0;
                    result = 1;
                }
            }
        }
    }
    return result;
}
asm(".align 2, 0");
