#include "frame.h"
#include "transition_object.h"
#include "resource_transition.h"

struct FrameObject *resource_create_transition(unsigned int kind)
{
    struct FrameObject *object = frame_allocate_scene_object();
    object->id = 24;
    object->flags = 0x2008;
    object->unknown_4c[0] = kind;
    transition_object_set_state((struct TransitionObject *)object, 0);
    object->on_step = g_resource_transition_steps[kind];
    return object;
}

asm(".align 2, 0");
