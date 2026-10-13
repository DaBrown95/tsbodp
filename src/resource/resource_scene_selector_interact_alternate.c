#include "resource_scene_selector.h"
#include "input.h"
#include "frame_scene_player.h"

struct ResourceSelectorInput {
    struct FrameScenePlayerSlot slots[4];
    unsigned char player_count, local_player;
};
struct ResourceSelectorCoordinates {
    unsigned char unknown00[26];
    short x;
    unsigned short unknown1c;
    short y;
};
void resource_scene_selector_interact_alternate(struct FrameObject *base, struct FrameObject *target)
{
    struct ResourceSceneSelector *object = (void *)base;
    struct ResourceSceneSelector *other = (void *)target;
    if (object->state != 18 && other->state == 16) {
        struct ResourceSelectorInput *input = (void *)&g_input_config;
        struct FrameActorObject *player = (void *)input->slots[input->local_player].object;
        unsigned char facing = frame_scene_effect_facing_available(target, base);
        unsigned int is_player = 0;
        unsigned int pressed;
        if (target->id == 0)
            is_player = 1;
        {
            unsigned short *keys = g_input_pressed;
            unsigned int player_index = player->unknown_13;
            pressed = *(unsigned char *)&keys[player_index] & 1;
        }
        if (is_player && facing) {
            struct ResourceSelectorCoordinates *coordinates = (void *)object;
            resource_scene_selector_activate_player(g_frame_scene_active_actor,
                coordinates->x, coordinates->y, (unsigned short)(object->oam.layer - 1));
            object->countdown = 3;
            if (pressed) {
                transition_object_set_state((struct FrameObject *)object, 18);
                frame_set_variant_state((struct FrameObject *)object, 0);
                transition_object_set_state(target, 0);
                object->indicator = target;
                input_clear();
            }
        }
    }
}
asm(".align 2, 0");
