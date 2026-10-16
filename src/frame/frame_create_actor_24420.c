#include "frame_actor_24420.h"

struct FrameObject *frame_create_actor_24420(struct FramePoint position, int direction)
{
    struct FrameActorObject *object = (struct FrameActorObject *)frame_allocate_scene_object();
    unsigned char *appearance;

    frame_set_position((struct FrameObject *)object, (unsigned int)position.x << 16, (unsigned int)position.y << 16);
    object->direction = direction;
    object->id = 0;
    frame_enable_object_flags((struct FrameObject *)object, 0x2400821d);
    object->on_step = frame_actor_step_24968;
    appearance = g_frame_actor_palette_pair_definition;
    frame_load_actor_group_palette(appearance, 0);
    frame_enable_parts((struct FrameObject *)object);
    frame_request_animation((struct FrameCommandObject *)object, 0);
    frame_set_part_variants((struct FrameObject *)object, 0,
                            g_actor_24420_part0_tables[appearance[0]], 0);
    frame_set_part_variants((struct FrameObject *)object, 1,
                            g_actor_24420_part1_tables[appearance[0]][appearance[2]], 0);
    frame_set_part_variants((struct FrameObject *)object, 2,
                            g_actor_24420_part2_variants,
                            g_actor_24420_palette_by_id[object->id]);
    frame_set_animation_variant((struct FrameObject *)object,
                               ((struct FrameActorGroupAnimationView *)object)->animation,
                               g_frame_scene_double_direction_variants[object->direction]);
    frame_set_part_order((struct FrameObject *)object, 0, 4);
    frame_set_part_order((struct FrameObject *)object, 1, 5);
    frame_enable_animation_part((struct FrameObject *)object, 2);
    if (object->direction > 8)
        object->oam.flip_x = 1;
    else
        object->oam.flip_x = 0;
    ((struct FrameActor24420CollisionView *)object)->collision = frame_scene_player_collision;
    object->before_step = resource_object_before_step;
    ((unsigned char *)object)[0x84] = 3;
    frame_update_actor_state((struct FrameObject *)object);
    transition_object_set_state(object, 16);
    frame_set_variant_state((struct FrameObject *)object, 2);
    audio_play_animation_cue(180);
    return (struct FrameObject *)object;
}
asm(".align 2,0");
