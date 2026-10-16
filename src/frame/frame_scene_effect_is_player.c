#include "frame_scene_player.h"
unsigned char frame_scene_effect_is_player(struct FrameSceneSavedEffect *effect)
{
    if (effect->owner == g_frame_scene_player_slots[0].object) return 1;
    return 0;
}
asm(".align 2,0");
