#include "frame_need_effect_placement.h"
#include "frame_grid_cells.h"
unsigned char frame_probe_need_effect_position(void *context,struct FrameObject *base,int x,int y)
{
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
 struct FramePoint saved_position;
 unsigned char saved_linked,result;
 frame_unregister_need_effect(context,base);
 saved_position=object->position;
 saved_linked=object->linked;
 object->position.x=(unsigned int)x<<16;
 object->position.y=(unsigned int)y<<16;
 result=frame_register_need_effect(context,base,0);
 object->position=saved_position;
 object->linked=1;
 frame_register_need_effect(context,base,1);
 object->linked=saved_linked;
 return result;
}
