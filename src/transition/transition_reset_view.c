#include "view_effects.h"
void transition_reset_view(unsigned char view)  {
    struct FramePoint zero=  {
        0,0
    };
    view_copy_point(&zero,&g_resource_view_motion[view].position);
    view_copy_point(&zero,&g_resource_view_motion[view].unknown0c);
    view_copy_point(&zero,&g_resource_view_motion[view].unknown14);
    view_copy_point(&zero,&g_resource_view_motion[view].target);
    g_resource_view_motion[view].mode=1;
    g_resource_view_motion[view].object=0;
    g_resource_view_motion[view].interpolate=1;
    g_resource_view_effects[view].phase=0;
    g_resource_view_effects[view].mode=0;
}
asm(".align 2, 0");
