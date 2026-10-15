#include "scene_contact_activity_one.h"
#define STATE g_scene_contact_activity_one_state
void scene_contact_activity_one_step(void) {
 switch(g_scene_request.unknown_10) {
 case 0:{struct FramePoint target;target.x=80*65536;target.y=1136*65536;
  transition_configure_view_move(target,10*65536,30,0);g_scene_request.unknown_10=1;break;}
 case 1:if(transition_get_view_mode(0)==0){g_scene_request.unknown_10=2;STATE->flags&=253;}break;
 case 2:{struct SceneContactActivityOneState **root=&g_scene_contact_activity_one_state;if((*root)->flags&2){
  if((*root)->attempts>2){(*root)->flags|=1;}
  else if(((struct FrameActorObject*)(*root)->primary)->variant_state!=0){
   transition_run_second(63,0);frame_stop_motion((*root)->primary);
   frame_set_position((*root)->primary,(unsigned int)g_scene_contact_activity_one_positions[(*root)->option].x*65536u,(unsigned int)g_scene_contact_activity_one_positions[(*root)->option].y*65536u);
   frame_request_animation((struct FrameCommandObject*)(*root)->primary,0);
   ((struct SceneContactActivityOneObject*)(*root)->primary)->layer=2;
   frame_set_variant_state((*root)->primary,0);break;
  }else{
   frame_update_map_view(0);transition_step_view(0);transition_run_first(63,0);
   transition_configure_alpha(2,20);transition_set_alpha(4,12);
  }
  (*root)->flags&=253;
 }break;}
 }
}
asm(".align 2,0");
