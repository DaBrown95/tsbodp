#include "frame_speed_exit_resource.h"
#include "frame.h"
#include "frame_actor_scene.h"
#include "frame_actor_speed_control.h"
#include "resource_object_payload.h"
void condition_refresh_scene(unsigned int row) {
 struct FrameActorSpeedGame *world;
 if(row>1) {
  world=(struct FrameActorSpeedGame *)&g_resource_game_state;
  world->exit_flag=0;
  switch(row) {
  case 2:world->world=4;world->saved_position.x=0x04300000;world->saved_position.y=0x02f10000;break;
  case 3:world->world=14;world->saved_position.x=0x02df0000;world->saved_position.y=0x00ff0000;break;
  case 4:world->world=9;world->saved_position.x=0x04b10000;world->saved_position.y=0x02220000;break;
  }
 }
}
