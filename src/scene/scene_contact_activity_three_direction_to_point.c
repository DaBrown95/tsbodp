#include "scene_contact_activity_three.h"
unsigned int scene_contact_activity_three_direction_to_point(int target_x,int target_y,int position_x,int position_y) {
 struct FramePoint delta;
 delta.x=(int)((unsigned int)target_x-(unsigned int)position_x);
 delta.y=(int)((unsigned int)target_y-(unsigned int)position_y);
 return view_direction_angle(delta);
}
asm(".align 2,0");
