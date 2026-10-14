#include "scene_text_bank.h"
void scene_text_bank_return_previous(void)
{
    if (g_scene_previous_request.unknown_00 == 6)
        resource_submit_scene(6, 0, g_scene_request.scene);
}
asm(".align 2,0");
