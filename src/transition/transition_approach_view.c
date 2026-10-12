#include "view_effects.h"
unsigned char transition_approach_view(struct FramePoint target,int speed,unsigned char view)  {
    struct FramePoint velocity,delta;
    int direction;
    if(g_resource_view_effects[view].elapsed<=63&&!g_resource_view_effects[view].done)  {
        speed=frame_fixed_multiply(speed,frame_sine((unsigned char)g_resource_view_effects[view].elapsed));
        g_resource_view_effects[view].elapsed+=2;
        if(g_resource_view_effects[view].elapsed>63)g_resource_view_effects[view].done=1;
    }
    else  {
        unsigned int distance=view_point_distance(g_resource_view_motion[view].position,target);
        if(distance<(unsigned int)frame_fixed_multiply(speed,0x140000))  {
            if(g_resource_view_effects[view].elapsed)  {
                speed=frame_fixed_multiply(speed,frame_sine((unsigned char)g_resource_view_effects[view].elapsed));
                g_resource_view_effects[view].elapsed-=2;
            }
        }
    }
    if(g_resource_view_motion[view].position.y>target.y+speed)  {
        if(g_resource_view_motion[view].position.x>target.x+speed)direction=7;
        else if(g_resource_view_motion[view].position.x<target.x-speed)direction=1;
        else direction=0;
    }
    else if(g_resource_view_motion[view].position.y<target.y-speed)  {
        if(g_resource_view_motion[view].position.x>target.x+speed)direction=5;
        else if(g_resource_view_motion[view].position.x<target.x-speed)direction=3;
        else direction=4;
    }
    else  {
        if(g_resource_view_motion[view].position.x>target.x+speed)direction=6;
        else if(g_resource_view_motion[view].position.x<target.x-speed)direction=2;
        else direction=8;
    }
    if(direction!=8)  {
        unsigned char angle;
        delta.x=target.x-g_resource_view_motion[view].position.x;
        delta.y=target.y-g_resource_view_motion[view].position.y;
        angle=view_direction_angle(delta);
        velocity.x=frame_fixed_multiply(g_view_direction_vectors[angle].x,speed);
        velocity.y=frame_fixed_multiply(g_view_direction_vectors[angle].y,speed);
        g_resource_view_motion[view].position.x+=velocity.x;
        g_resource_view_motion[view].position.y+=velocity.y;
        direction=0;
    }
    else  {
        g_resource_view_motion[view].position.x=target.x;
        g_resource_view_motion[view].position.y=target.y;
    }
    return direction;
}
asm(".align 2, 0");
