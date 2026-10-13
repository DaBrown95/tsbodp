#include "scene_environment.h"
void scene_refresh_environment(void)
{
 void *palette=0;
 struct SceneTimeTriggers *world=(struct SceneTimeTriggers *)g_scene_world_state;
 unsigned int period=display_time_period(&world->time);
 if(g_scene_context.period!=period){g_scene_context.period=period;palette=scene_palette_source();}
 else if(world->enabled){
  if((unsigned char)display_time_equal(&world->time,&world->first,6)){
   if(!(g_game_flags&0x10)&&g_scene_id<=14){background_animation_load(1);background_animation_configure_alpha();}
   g_scene_context.flags|=1;
  }else if((unsigned char)display_time_equal(&world->time,&world->second,6)){
   if(!(g_game_flags&0x10)){background_animation_stop_default();background_animation_configure_alpha();}
   g_scene_context.flags&=~1u;
  }
  palette=scene_palette_source();
 }
 if(palette)g_scene_context.unknown_08=display_create_palette_block(64,192,8,0,1,palette);
}
