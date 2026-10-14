#include "frame_actor_action_query.h"

static __inline signed char actor_action_find_inline(unsigned int id)
{
 unsigned int index=0;
 struct FrameActorActionDefinition *entry=g_frame_actor_action_definitions;
 for(;index<=35;entry++,index++) {
  if(entry->id==id) return index;
 }
 return -1;
}

unsigned int frame_actor_has_action(unsigned int id)
{
 return actor_action_find_inline(id)!=-1;
}
