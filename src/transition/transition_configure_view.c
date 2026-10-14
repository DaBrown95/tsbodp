#include "view_effects.h"
#include "view_configuration.h"
void transition_configure_view(struct TransitionViewObject *object,struct FramePoint dimensions,unsigned char index)
{
 g_resource_view_motion[index].object=(struct FrameObject *)object;
 g_resource_view_dimensions[index].x=dimensions.x;
 g_resource_view_dimensions[index].y=dimensions.y;
 g_resource_view_motion[index].target.x=g_resource_view_motion[index].position.x=((struct FrameObject *)object)->position.x;
 g_resource_view_motion[index].target.y=g_resource_view_motion[index].position.y=((struct FrameObject *)object)->position.y;
}
