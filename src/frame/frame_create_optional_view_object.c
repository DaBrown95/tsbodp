#include "frame_optional_view.h"
struct FrameObject *frame_create_optional_view_object(unsigned char group,unsigned char slot)
{
 struct FrameOptionalViewPayload *payload=(struct FrameOptionalViewPayload *)resource_get_object_payload(group,slot);
 struct FrameObject *base=frame_allocate_scene_object();
 struct FrameOptionalViewObject *object=(struct FrameOptionalViewObject *)base;
 frame_set_position(base,(unsigned int)(int)payload->x<<16,(unsigned int)(int)payload->y<<16);
 object->view_x=payload->view_x;
 object->view_y=payload->view_y;
 object->actor_direction=payload->direction;
 object->id=payload->id;
 object->flags=0x2040c;
 object->on_step=frame_optional_view_step;
 object->state=0;
 object->resource_loaded=0;
 object->on_interact=frame_optional_view_interact;
 object->bound_x0=-payload->bound_x;
 object->bound_x1=payload->bound_x;
 object->bound_y0=-payload->bound_y;
 object->bound_y1=payload->bound_y;
 ((struct FrameOptionalViewCollisionFlags *)base)->flag_b4=1;
 ((struct FrameOptionalViewCollisionFlags *)base)->flag_af=1;
 object->first_transition=payload->first_transition;
 object->second_transition=payload->second_transition;
 return base;
}
