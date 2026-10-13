#include "resource_scene_selector.h"
#include "scene_request.h"

void resource_scene_selector_complete(struct FrameObject *base)
{
    struct ResourceSceneSelector *object = (void *)base;
    unsigned int canceled;
    frame_stop_motion(object->indicator);
    canceled = 0;
    switch (object->variant_state) {
    case 0:
        g_actor_scene_result_id.id = 0x1813;
        g_resource_selector_notice.active = 0;
        g_resource_selector_notice.mode = 0;
        g_resource_selector_notice.kind = 0;
        scene_submit_default_request(2);
        frame_set_variant_state((struct FrameObject *)object, 0x37);
        break;
    case 0x37:
        if (g_scene_previous_request.parameter != 0xffffffff) {
            g_scene_mode_bytes[0] = object->parameter;
            resource_submit_scene(1, 0, object->selector);
        } else {
            canceled = 1;
        }
        break;
    }
    if (canceled == 1) {
        transition_object_set_state((struct FrameObject *)object, 0);
        frame_set_variant_state((struct FrameObject *)object, 1);
        transition_object_set_state(object->indicator, 16);
        frame_set_variant_state(object->indicator, 2);
        frame_request_animation((struct FrameCommandObject *)object->indicator, 1);
    }
}
asm(".align 2, 0");
