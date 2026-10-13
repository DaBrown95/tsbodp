#include "frame_scene_player.h"

struct ResourceArenaHeader;
extern struct ResourceArenaHeader *g_resource_arena;

/* AFA8 copies these eight-byte records after two observed halfwords. */
struct ResourceSpawnArena {
    unsigned short bytes, count;
    struct FrameScenePlayerSpawnResource records[1];
};

struct FrameScenePlayerSpawnResource *
frame_scene_player_spawn_resource(unsigned char group, unsigned char slot)
{
    struct FrameScenePlayerSpawnResource *result =
        g_frame_scene_player_spawn_defaults + slot;
    unsigned char index = 0;
    struct ResourceSpawnArena *input = (struct ResourceSpawnArena *)g_resource_arena;
    unsigned int initial_count = input->count;

    if (index < initial_count) {
        unsigned char *arena = (unsigned char *)input;
        unsigned short count = initial_count;
        do {
            unsigned int record_offset = index * 8;
            struct ResourceSpawnArena *view =
                (struct ResourceSpawnArena *)(arena + record_offset);
            if (view->records[0].group == group && view->records[0].slot == slot) {
                result = (struct FrameScenePlayerSpawnResource *)(arena + (record_offset + 4));
                break;
            }
            index++;
        } while (index < count);
    }
    return result;
}
asm(".align 2,0");
