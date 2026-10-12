#include "frame_actor_needs.h"
#include "frame_actor_social.h"
#include "frame_actor_actions.h"
void frame_note_actor_action(unsigned short id)
{
 unsigned int index=6;
 if(id==209) frame_add_game_value(5000);
 else {
  switch(id) {
  case 211:index=5;break;
  case 212:index=0;break;
  case 213:index=1;break;
  case 214:index=3;break;
  case 215:index=4;break;
  case 216:index=2;break;
  }
  if(index!=6) frame_advance_parameter_level(g_frame_actor_social_probe,index);
 }
}
