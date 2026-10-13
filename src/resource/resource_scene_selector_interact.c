#include "resource_scene_selector.h"
#include "input.h"
#include "resource_conditions.h"

static inline unsigned int selector_needs_input(struct ResourceSceneSelector *object)
{
    /* Keep the computed requirement distinct from its captured caller value. */
    register unsigned int required asm("r3") = 0;
    unsigned short subtype = object->subtype;
    if ((unsigned short)(subtype - 1) <= 2 || subtype == 5)
        required = 1;
    return required;
}

static inline struct ResourceSceneSelector *selector_view(struct FrameObject *base)
{
    return (void *)base;
}

void resource_scene_selector_interact(struct FrameObject *base, struct FrameObject *target)
{
    unsigned int allowed = 0;
    g_resource_selector_world.flag42f = 1;
    if (selector_view(base)->state == 0) {
        /* Both bound values are consumed before any call. */
        register unsigned int needs_input asm("r1") = selector_needs_input(selector_view(base));
        if (selector_view(target)->id == 0 && (selector_view(target)->state == 16 || selector_view(target)->state == 27)) {
            allowed = 1;
            if (needs_input) {
                unsigned short *keys = g_input_pressed;
                allowed &= keys[selector_view(base)->player_index];
            }
        }
        if (allowed == 1) {
            if (g_resource_selector_world.mode42e == 1 && selector_view(base)->selector > 14)
                allowed = 0;
            if (allowed == 1) {
                if (selector_view(base)->id == 20 && selector_view(base)->second_hour != 0) {
                    unsigned int first = selector_view(base)->first_hour;
                    unsigned int second = selector_view(base)->second_hour;
                    if (first < second) {
                        int hour = g_resource_selector_world.clock.hour;
                        if (hour < (int)first || hour >= (int)second) {
                            allowed = 0;
                            selector_view(target)->state = 0;
                            selector_view(base)->state = 4;
                            selector_view(base)->indicator = (struct FrameObject *)selector_view(target);
                        }
                    } else {
                        int hour = g_resource_selector_world.clock.hour;
                        if (hour < (int)first && hour >= (int)second) {
                            allowed = 0;
                            selector_view(target)->state = 0;
                            selector_view(base)->state = 4;
                            selector_view(base)->indicator = (struct FrameObject *)selector_view(target);
                        }
                    }
                }
                if (allowed == 1) {
                    if (selector_view(base)->subtype != 2) {
                        if (selector_view(base)->subtype != 5)
                            goto submit_scene;
                        goto subtype_five;
                    }
                    if ((unsigned char)condition_is_complete(2, 4, 2)) {
                        audio_play_animation_cue(47);
                        frame_set_variant_state((struct FrameObject *)selector_view(base), 11);
                        frame_enable_object_flags((struct FrameObject *)selector_view(base), 16);
                        frame_disable_object_flags((struct FrameObject *)selector_view(base), 4);
                        frame_stop_motion((struct FrameObject *)selector_view(target));
                        transition_object_set_state((struct FrameObject *)selector_view(target), 0);
                    }
subtype_five:
                    if (selector_view(base)->subtype == 5) {
                        audio_play_animation_cue(47);
                        frame_set_variant_state((struct FrameObject *)selector_view(base), 11);
                        frame_enable_object_flags((struct FrameObject *)selector_view(base), 16);
                        frame_disable_object_flags((struct FrameObject *)selector_view(base), 4);
                        frame_stop_motion((struct FrameObject *)selector_view(target));
                        transition_object_set_state((struct FrameObject *)selector_view(target), 0);
                    }
                }
            }
        }
    }
    goto finished;
submit_scene:
    g_scene_mode_bytes[0] = selector_view(base)->parameter;
    g_resource_selector_world.selected_actor = resource_select_actor(g_scene_id, selector_view(base)->selector);
    resource_submit_scene(1, 0, selector_view(base)->selector);
finished:
    return;
}
asm(".align 2, 0");
