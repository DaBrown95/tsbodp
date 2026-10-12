#include "view_effects.h"
#include "resource_view_actor.h"
void resource_prepare_object(struct FrameObject *object)  {
    object->on_step=resource_view_actor_tick;
    g_transition_view_context.views[g_transition_view_context.current_view].flags|=1;
}
