#include "view_effects.h"
void transition_configure_view_move(struct FramePoint target,int speed,unsigned short delay,unsigned char view)  {
    g_resource_view_motion[view].target.x=target.x;
    g_resource_view_motion[view].target.y=target.y;
    g_resource_view_motion[view].speed=speed;
    g_resource_view_motion[view].delay=delay;
    g_resource_view_motion[view].mode=2;
    g_resource_view_effects[view].mode=0;
}
asm(".align 2, 0");
