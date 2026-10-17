#include "frame_scene_player_update.h"

void frame_scene_player_step_1dfe4(struct FrameObject *base)
{
    struct FrameActorObject *actor = (struct FrameActorObject *)base;
    signed char *directions;
    unsigned int limit;

    if ((unsigned char)(actor->variant_state - 51) > 3)
        frame_update_actor_needs(actor->actor_state, actor);
    frame_actor_choose_need_action(&g_display_menu_result_local_needs, actor);
    frame_run_actor_state((struct FrameObject *)actor);
    if (actor->flags & 0x20000000) {
        directions = g_frame_scene_double_direction_variants;
        limit = 8;
    } else {
        directions = g_frame_actor_direction_variants_signed;
        limit = 4;
    }
    if (actor->pending_updates & 0x16) {
        if (actor->pending_updates & 0x14) {
            unsigned char *appearance = g_frame_actor_palette_pair_definition;
            signed char *animation;
            int group;
            signed char variant;

            frame_bind_actor_group((struct FrameObject *)actor, appearance);
            animation = &actor->requested_animation;
            group = *animation;
            variant = directions[actor->direction];
            frame_set_animation_variant((struct FrameObject *)actor, group, variant);
            if (appearance[0]) {
                unsigned char **commands = g_frame_actor_commands_kind1;
                signed char requested = *animation;

                frame_set_animation_commands((struct FrameObject *)actor, commands[requested], 0);
            } else {
                unsigned char **commands = g_frame_scene_player_commands_kind2;
                signed char requested = *animation;

                frame_set_animation_commands((struct FrameObject *)actor, commands[requested], 0);
            }
        }
        if (actor->direction > limit)
            actor->oam.flip_x = 1;
        else
            actor->oam.flip_x = 0;
    }
    actor->pending_updates = 0;
    g_frame_scene_actor_selection.unknown0b[0x42f - 0x0b] = 0;
}
