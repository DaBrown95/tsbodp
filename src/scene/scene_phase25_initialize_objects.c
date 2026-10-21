#include "scene_phase25.h"
#include "frame_scene_player.h"
#include "frame_actor_speed_control.h"
#include "frame_actor_state.h"
#include "display_scene_lifecycle.h"
#include "display_transient_definition.h"
#include "scene_map_selection.h"
#include "scene_link_menu_actions.h"
#include "scene_startup.h"

/* Provisional resource names for the two backgrounds and the object palette. */
extern const struct BackgroundResource g_scene_phase25_object_background3;
extern const struct BackgroundResource g_scene_phase25_object_background2;
extern const unsigned short g_scene_phase25_object_palette[];

void scene_phase25_initialize_objects(void)
{
    struct FrameActorObject *actor;
    struct FrameScenePlayerGroup *group;
    struct FrameObject **objects;
    struct FrameTransientEffect **effect;

    display_load_background(3, &g_scene_phase25_object_background3, 0, 0, 0, 0);
    display_load_background_dma(2, &g_scene_phase25_object_background2, 599, 0, 0, 0);
    display_hide_background(0);
    frame_initialize_transient_definition(0, 2, &g_scene_startup_transient2);
    actor = (struct FrameActorObject *)frame_allocate_object(0);
    actor->flags = 0x04000011;
    actor->direction = 4;
    frame_enable_parts((struct FrameObject *)actor);
    group = &g_frame_scene_player_group;
    frame_load_actor_group_palette(group, 0);
    frame_acquire_palette_slot((struct FrameObject *)actor, 0);
    frame_bind_actor_group((struct FrameObject *)actor, group);
    frame_set_animation_variant((struct FrameObject *)actor, 1,
        g_frame_actor_direction_variants_signed[actor->direction]);
    if (group->mode)
        frame_set_animation_commands((struct FrameObject *)actor,
            g_frame_actor_commands_kind1[actor->requested_animation], 0);
    else
        frame_set_animation_commands((struct FrameObject *)actor,
            g_frame_scene_player_commands_kind2[actor->requested_animation], 0);
    frame_set_part_order((struct FrameObject *)actor, 1, 4);
    frame_set_part_order((struct FrameObject *)actor, 0, 5);
    frame_set_part_order((struct FrameObject *)actor, 2, 6);
    frame_enable_animation_part((struct FrameObject *)actor, 0);
    objects = g_display_scene_frame_objects;
    objects[1] = (struct FrameObject *)actor;
    frame_set_position((struct FrameObject *)actor, 116 * 65536, 91 * 65536);
    objects[1]->flags &= ~1U;
    ((struct FrameActorObject *)objects[1])->oam.layer = 2;
    objects[1]->flags |= 0x80000;
    objects[0] = frame_create_scene_object(208, 316, 15, 2);
    objects[0]->flags |= 0x200000;
    transition_object_set_state(objects[0], 14);
    frame_set_variant_state(objects[0], 56);
    ((struct FrameActorObject *)objects[0])->need_timer = 30;
    objects[0]->flags |= 0x100000;
    display_load_palette_alternate(g_scene_phase25_object_palette, 32, 16);
    effect = &g_frame_actor_speed_effect;
    *effect = frame_create_transient_effect(2, 0, 2);
    if (*effect) {
        (*effect)->owner = objects[0];
        (*effect)->phase = 3;
        {
            struct FrameTransientEffect *active = *effect;
            active->flags |= 0x20580;
            active->width = 8;
            active->height = 20;
            active->enabled = 1;
        }
        {
            struct FrameTransientEffect *active = *effect;
            active->unknown34 = 0;
            active->direction = g_actor_reverse_directions[4];
        }
        (*effect)->rate = 0x10000;
        (*effect)->unknown43 = 0;
    }
    transition_run_first(63, 0);
}

asm(".align 2, 0");
