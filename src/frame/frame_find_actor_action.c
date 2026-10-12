#include "frame_actor_actions.h"
signed char frame_find_actor_action(unsigned int id)
{
 unsigned int index=0;
 struct FrameActorActionDefinition *entry=g_frame_actor_action_definitions;
 for(;index<=35;entry++,index++) {
  if(entry->id==id) return index;
 }
 return -1;
}
