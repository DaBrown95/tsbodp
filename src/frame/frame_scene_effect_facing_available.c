#include "frame_scene_effect.h"
unsigned char frame_scene_effect_facing_available(struct FrameObject *base,struct FrameObject *other_base) {
 struct FrameActorObject *object=(struct FrameActorObject *)base;
 struct FrameActorObject *other=(struct FrameActorObject *)other_base;
 struct FramePoint first,second,delta;
 unsigned char direction;
 short facing;
 frame_point_to_integer(&object->position,&first);
 frame_point_to_integer(&other->position,&second);
 delta.x=second.x-first.x;delta.y=second.y-first.y;
 direction=frame_direction_from_velocity(delta);
 facing=object->direction;
 switch(direction){
 case 0:if((unsigned short)facing<=1 || (short)facing==7)return 1;break;
 case 1:if((unsigned short)facing<=2)return 1;break;
 case 2:if((unsigned short)(facing-1)<=2)return 1;break;
 case 3:if((unsigned short)(facing-2)<=2)return 1;break;
 case 4:if((unsigned short)(facing-3)<=2)return 1;break;
 case 5:if((unsigned short)(facing-4)<=2)return 1;break;
 case 6:if((unsigned short)(facing-5)<=2)return 1;break;
 case 7:if(facing==7 || facing==0 || facing==6)return 1;break;
 }
 return 0;
}
