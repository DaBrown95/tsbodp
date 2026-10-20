#include "frame_actor_items.h"
#include "frame_actor_speed.h"
#include "frame_constructor.h"
#include "input.h"
#include "frame_random.h"

#define STATE ((struct FrameActorItemState *)g_scene_contact_state)

void frame_actor_update_24720(struct FrameObject *base)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    struct FramePoint velocity;
    unsigned int direction;
    unsigned char player = object->unknown_13;
    int state = object->variant_state;

    if (state == 2) goto movement_two;
    if (state > 2) goto movement_other;
    goto complete;

movement_other:
    if (state == 3) goto movement_three;
    if (state == 8) goto movement_eight;
    goto complete;

movement_two:
    if (g_input_current[player] & 1) {
        frame_set_directional_acceleration((struct FrameObject *)object, object->direction, 32768);
        object->need_timer = 3;
        frame_set_variant_state((struct FrameObject *)object, 3);
    } else if (frame_approximate_vector_length(object->velocity) <
               frame_approximate_vector_length(object->acceleration)) {
        object->acceleration.x = 0;
        object->acceleration.y = 0;
        frame_make_direction_vector(&velocity, object->direction, 32768);
        object->velocity.x = velocity.x;
        object->velocity.y = velocity.y;
    }
    goto complete;

movement_three:
    if (--object->need_timer == 65535) {
        {
            register InputU8 argument asm("r0") = player;
            direction = input_rotate_direction(argument, object->direction);
        }
        object->need_timer = 3;
    } else {
        direction = 16;
    }
    if (g_input_current[player] & 1) {
        if (direction != 16) {
            frame_set_actor_turn_direction((struct FrameObject *)object, (unsigned char)direction);
            frame_set_directional_acceleration((struct FrameObject *)object, object->direction, 32768);
        }
        frame_make_direction_vector(&velocity, object->direction,
            g_frame_actor_item_options[STATE->option].speed);
        if (frame_approximate_vector_length(object->velocity) >=
            frame_approximate_vector_length(velocity)) {
            object->acceleration.x = 0;
            object->acceleration.y = 0;
            object->velocity.x = velocity.x;
            object->velocity.y = velocity.y;
        }
    } else {
        frame_make_direction_vector(&object->velocity, object->direction,
            g_frame_actor_item_options[STATE->option].speed);
        frame_set_variant_state((struct FrameObject *)object, 2);
        frame_approximate_vector_length(object->velocity);
        frame_set_directional_acceleration((struct FrameObject *)object, object->direction, -32768);
    }
    goto complete;

movement_eight:
    if (!(object->flags & 32)) {
        frame_enable_object_flags((struct FrameObject *)object, 32);
        object->need_timer = frame_random_range(17, 31);
        object->velocity.x = 0;
        object->velocity.y = 0;
        object->acceleration.x = 0;
        object->acceleration.y = 0;
    } else if (--object->need_timer == 65535) {
        frame_set_variant_state((struct FrameObject *)object, 2);
        frame_disable_object_flags((struct FrameObject *)object, 32);
    } else {
        direction = object->direction;
        direction++;
        if (direction == 16) direction = 0;
        frame_set_actor_turn_direction((struct FrameObject *)object, (unsigned char)direction);
    }
    goto complete;

complete:
    return;
}
asm(".align 2,0");
