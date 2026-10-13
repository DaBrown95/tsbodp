#include "save_world_initialization.h"

void save_world_initialize_record(void *pointer)
{
    if (g_save_world_view.unknown00 == 0) {
        save_world_empty_hook_32000((unsigned char *)pointer + 0x18);
        save_world_empty_hook_3d170((unsigned char *)pointer + 0x88);
    }
    save_world_initialize_relations((struct DisplayMenuRelationState *)pointer);
    frame_reset_actor_needs((struct FrameActorNeedState *)
                            ((unsigned char *)pointer + 0xa0));
}
asm(".align 2, 0");
