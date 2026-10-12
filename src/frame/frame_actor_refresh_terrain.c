#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_social.h"
void frame_actor_refresh_terrain(struct FrameObject *object)
{
 struct FramePoint point={((short*)&object->next_position)[1],((short*)&object->next_position)[3]};
 ((struct FrameActorTerrainState*)object)->terrain=frame_map_terrain_at(point);
 if(((struct FrameActorTerrainState*)object)->terrain==1) {
  if(!(object->flags&0x4000)) {
   object->flags|=0x4000;
   frame_refresh_velocity(object);
  }
 } else if(object->flags&0x4000) {
  object->flags&=~0x4000;
  frame_refresh_velocity(object);
 }
}
