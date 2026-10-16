#include "save_world_defaults.h"

void save_world_reset_defaults(void)
{
    unsigned char *world = ((struct SaveWorldDefaultState *)&g_resource_game_state)->bytes;
    unsigned char *player;
    heap_clear(world, 0, 1876);
    actor_entry_prepare((struct ActorEntryContext *)(world + 220));
    save_world_original_reset_hook();
    player = (unsigned char *)&g_scene_contact_serial_player_input;
    heap_clear(player, 0, 52);
    player[48] = 1;
    frame_set_game_value(0);
    runtime_copy_padded_string(world + 16, g_save_world_default_name, 16);
}
