#include "frame_actor_needs.h"
#include "frame_actor_social.h"
#include "frame_actor_interaction.h"
void frame_note_interaction_condition(unsigned int id)
{
 if((unsigned int)(g_frame_world_id-16)<=1) {
  if(id==30) resource_set_triple(0,2,0);
  if(id==49) resource_set_triple(0,2,1);
  if(id==4) resource_set_triple(0,2,2);
  if(id==63) resource_set_triple(0,2,3);
  if(id==54) resource_set_triple(0,2,4);
  if(id==109) resource_set_triple(1,1,2);
 }
}
