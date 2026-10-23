#include "frame_actor_attachment_counter_choices.h"

void frame_remove_counter_attachment_selection(void)
{
    if (resource_count_selectable_actor_entries())
        resource_remove_random_selectable_actor_entry();
}
asm(".align 2,0");
