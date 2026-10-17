#include "frame.h"
#include "transition_object.h"
#include "background_animation.h"
#include "resource_transition.h"
#include "resource_groups.h"
#include "scene_retention.h"

void transition_object_tick_windows(struct FrameObject *input)
{
    struct TransitionObject *object = (struct TransitionObject *)input;
    register struct TransitionViewObject *view asm("r8") =
        g_transition_view_context.views[g_transition_view_context.current_view].object;
    struct FramePoint point;

    switch (object->state) {
    case 0:
        if (--object->delay == 0xFFFF) {
            g_transition_first_handlers[object->first_kind](0x3F);
            background_animation_load(g_background_animation.transfer_enabled);
            background_animation_configure_alpha();
            transition_object_set_state(object, 1);
        }
        break;
    case 1:
        object->flags |= 2;
        break;
    case 3:
        if (--object->countdown == -1)
            transition_object_set_state(object, 5);
        break;
    case 4:
        g_transition_second_handlers[object->first_kind](0x3F);
        point.x = (unsigned int)object->position_x << 16;
        point.y = (unsigned int)object->position_y << 16;
        transition_set_view_mode(1, g_transition_view_context.current_view);
        transition_set_view_position(point, g_transition_view_context.current_view);
        resource_activate_groups(object->layer_a, object->layer_b);
        transition_object_set_state(object, 6);
        object->delay = 1;
        break;
    case 5:
        g_transition_second_handlers[object->second_kind](0x3F);
        frame_disable_primary_object_flags(0x2000000);
        transition_set_view_mode(0, g_transition_view_context.current_view);
        {
            struct TransitionViewObject *current = view;
            transition_set_view_position(
                (struct FramePoint){current->x, current->y},
                g_transition_view_context.current_view);
        }
        transition_configure_view(view, g_transition_view_configuration.point,
            g_transition_view_context.current_view);
        transition_object_set_state(object, 0);
        object->delay = 1;
        break;
    case 6:
        if (--object->delay == 0xFFFF) {
            g_transition_first_handlers[object->second_kind](0x3F);
            transition_object_set_state(object, 3);
        }
        break;
    case 2:
        break;
    }
    object->pending = 0;
}
