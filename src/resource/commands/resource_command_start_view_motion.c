#include "resource_commands.h"
void resource_command_start_view_motion(struct ResourceProgramRecord *command)  {
    struct FrameObject *object=resource_get_object(COMMAND_BYTE(4),COMMAND_BYTE(5));
    unsigned int index;
    if(object) {
        for(index=0;index<g_transition_view_context.count;index++) {
            struct FrameObject *view;
            transition_set_view_mode(5,index);
            view=(struct FrameObject *)g_transition_view_context.views[index].object;
            if(!object->id)g_resource_view_effects[index].object=view;
            else g_resource_view_effects[index].object=object;
            g_resource_view_effects[index].parameter=resource_scale_value(COMMAND_SIGNED_HALF(8));
            g_resource_view_effects[index].phase=COMMAND_HALF(10);
            if(!index) {
                g_resource_view_effects[index].group_a=COMMAND_BYTE(6);
                g_resource_view_effects[index].group_b=COMMAND_BYTE(7);
            }
            else {
                g_resource_view_effects[index].group_a=0;
                g_resource_view_effects[index].group_b=0;
            }
            g_resource_view_effects[index].mode=1;
            g_resource_view_effects[index].variant=OBJECT_BYTE(view,0x4e);
            g_resource_view_effects[index].saved_velocity=view->velocity;
            g_resource_view_effects[index].flags=0;
            view->velocity.x=0;
            view->velocity.y=0;
            g_resource_view_effects[index].elapsed=0;
            g_resource_view_effects[index].done=0;
        }
    }
}
asm(".align 2, 0");
