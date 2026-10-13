#include "resource_scene_selector.h"

void resource_scene_selector_tick(struct FrameObject *base)
{
    struct ResourceSceneSelector *object = (void *)base;
    char buffer[20];
    union ResourceSelectorClock first, second;
    first.record = g_resource_selector_clock;
    second.record = g_resource_selector_clock;
    switch (object->state) {
    case 0:
        switch (object->variant_state) {
        case 1:
            if (object->countdown && !--object->countdown)
                resource_selector_player_step_2fb74(g_frame_scene_active_actor);
            break;
        case 11:
            if ((unsigned char)frame_object_has_flags((struct FrameObject *)object, 0x400000)) {
                frame_set_variant_state((struct FrameObject *)object, 1);
                frame_disable_object_flags((struct FrameObject *)object, 0x400010);
                g_scene_mode_bytes[0] = object->parameter;
                g_resource_selector_world.selected_actor =
                    resource_select_actor(g_scene_id, object->selector);
                resource_submit_scene(1, 0, object->selector);
            }
            break;
        }
        break;
    case 18:
        resource_selector_state_2712c((struct FrameObject *)object);
        break;
    case 1:
        frame_run_actor_state((struct FrameObject *)object);
        break;
    case 3:
        if (--object->countdown == -1)
            object->state = 0;
        break;
    case 4:
        first.fields.hour = object->first_hour;
        display_time_format(&first.record, buffer, 0x1851);
        display_text_copy_field_one(buffer);
        second.fields.hour = object->second_hour;
        display_time_format(&second.record, buffer, 0x1851);
        display_text_copy_field_two(buffer);
        g_actor_scene_result_id.id = 0x1856;
        g_resource_selector_notice.active = 0;
        g_resource_selector_notice.mode = 1;
        g_resource_selector_notice.kind = 4;
        display_text_copy_field_zero(display_scene_lookup_text(g_resource_selector_labels[object->selector]));
        scene_submit_default_request(2);
        frame_set_actor_direction(object->indicator, 4);
        frame_request_animation((struct FrameCommandObject *)object->indicator, 0x55);
        frame_set_variant_state(object->indicator, 0x36);
        object->state = 5;
        break;
    case 5:
        ((struct ResourceSceneSelector *)object->indicator)->state = 16;
        object->indicator = 0;
        object->countdown = 60;
        object->state = 3;
        break;
    }
}
asm(".align 2, 0");
