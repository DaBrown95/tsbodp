#include "frame_scene_player.h"
void frame_scene_effect_state_8e14(struct FrameObject *);
void frame_scene_effect_state_91f4(struct FrameObject *);
void frame_scene_effect_update_950c(struct FrameObject *);
void frame_scene_effect_refresh(struct FrameObject *);
void frame_scene_effect_tick(struct FrameObject *base) {
 struct FrameActorObject *object=(struct FrameActorObject *)base;
 unsigned char direction;
 switch(object->state) {
 case 29: frame_scene_effect_state_8e14((struct FrameObject *)object);break;
 case 30: frame_scene_effect_state_91f4((struct FrameObject *)object);break;
 }
 frame_scene_effect_update_950c((struct FrameObject *)object);
 direction=object->direction;
 if((object->pending_updates&8) || ((object->pending_updates&16) && (object->velocity.x || object->velocity.y))) frame_refresh_velocity((struct FrameObject *)object);
 if(object->pending_updates&0x14) frame_scene_effect_refresh((struct FrameObject *)object);
 if(direction>4) object->oam.flip_x=1;
 else object->oam.flip_x=0;
 object->pending_updates=0;
}
