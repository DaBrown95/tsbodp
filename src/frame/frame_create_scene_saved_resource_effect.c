#include "frame_scene_player.h"
#include "resource_object_payload.h"

/* Partial serialized payload view; its complete record length is unknown. */
struct ResourceSavedEffectParameters {
    unsigned char unknown00[4];
    short x, y;
    unsigned char kind;
};

struct FrameSceneSavedEffect *frame_create_scene_saved_resource_effect(
    unsigned char group, unsigned char slot)
{
    struct ResourceSavedEffectParameters *data =
        (struct ResourceSavedEffectParameters *)resource_get_object_payload(group, slot);

    return frame_create_scene_saved_effect(data->kind,
        (unsigned int)data->x << 16, (unsigned int)data->y << 16);
}

asm(".align 2,0");
