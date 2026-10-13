#include "frame_scene_player.h"
#include "resource_conditions.h"
unsigned char frame_world_in_idle_exclusion_set(unsigned int);
unsigned char frame_scene_actor_allowed(unsigned int actor,unsigned int world,const struct DisplayTimeRecord *data) {
 unsigned char table_index;
 const unsigned char **table;
 unsigned char slot;
 if(!g_frame_scene_actor_eligibility_enabled) return 1;
 if(actor==31 && condition_is_complete(4,4,2)==1) {
  if(world==37) return 1;
  return 0;
 }
 table_index=actor-6;
 if(actor==g_frame_scene_actor_selection.actor) {
  if(frame_world_in_idle_exclusion_set(world)!=1) return 0;
  if((unsigned char)(g_frame_scene_actor_selection.current_world-9)>7) return 1;
  return 0;
 }
 if(actor<=5) return 1;
 {unsigned int base=(unsigned int)g_frame_scene_actor_world_tables; table=(const unsigned char**)((table_index<<2)+base);}
 if(!*table) return 1;
 slot=display_time_weekday(data);
 if(((*table)+data->hour*8)[slot]==world) return 1;
 return 0;
}
