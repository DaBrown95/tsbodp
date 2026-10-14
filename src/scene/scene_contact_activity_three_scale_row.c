#include "scene_contact_activity_three.h"
void scene_contact_activity_three_scale_row(struct FrameObject *base,int x,int y) {
 if(((struct SceneContactActivityThreeObject*)base)->direction>16)frame_set_affine_scale((struct FrameAffineObject*)base,(int)(0u-(unsigned int)x),y,0);
 else frame_set_affine_scale((struct FrameAffineObject*)base,x,y,0);
 if(x>65536||y>65536)((struct SceneContactActivityThreeObject*)base)->mode=3;
}
asm(".align 2,0");
