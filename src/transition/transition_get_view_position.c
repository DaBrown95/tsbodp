#include "view_effects.h"
void transition_get_view_position(struct FramePoint *point,unsigned char index) {
 point->x=g_resource_view_motion[index].position.x;
 point->y=g_resource_view_motion[index].position.y;
}
asm(".align 2, 0");
