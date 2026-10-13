#include "frame_scene_player.h"
struct FrameObject *frame_scene_player_actor(unsigned char player) {
 struct FrameActorObject *object=(struct FrameActorObject *)frame_allocate_object(0);
 unsigned char multiplier;unsigned int limit;
 signed char *directions;
 struct FrameScenePlayerGroup *group;
 object->flags=0x1404025d;
 if(!g_frame_scene_player_mode.mode){multiplier=1;limit=4;directions=g_frame_actor_direction_variants_signed;}
 else {multiplier=2;limit=8;object->flags|=0x20000000;directions=g_frame_scene_double_direction_variants;}
 if(g_scene_mode_bytes[player]!=255){
  struct FrameScenePlayerSpawnResource *start=frame_scene_player_spawn_resource(g_scene_mode_bytes[player],player);
  frame_set_position((struct FrameObject *)object,(unsigned int)start->x<<16,(unsigned int)start->y<<16);
  object->direction=start->direction*multiplier;
 }else{
  frame_set_position((struct FrameObject *)object,(unsigned int)g_frame_scene_player_fallback.x<<16,(unsigned int)g_frame_scene_player_fallback.y<<16);
  object->direction=g_frame_scene_player_fallback.direction;
 }
 object->default_state=16;
 object->speed=0x30000;
 frame_scene_initialize_player_state((struct FrameObject *)object,player);
 frame_enable_parts((struct FrameObject *)object);
 group=&g_frame_scene_player_group;
 frame_load_actor_group_palette(group,0);
 frame_acquire_palette_slot((struct FrameObject *)object,0);
 frame_bind_actor_group((struct FrameObject *)object,group);
 frame_set_animation_variant((struct FrameObject *)object,object->requested_animation,directions[object->direction]);
 if(group->mode)frame_set_animation_commands((struct FrameObject *)object,g_frame_actor_commands_kind1[object->requested_animation],0);
 else frame_set_animation_commands((struct FrameObject *)object,g_frame_scene_player_commands_kind2[object->requested_animation],0);
 frame_set_part_order((struct FrameObject *)object,0,4);
 frame_set_part_order((struct FrameObject *)object,1,5);
 frame_set_part_order((struct FrameObject *)object,2,6);
 frame_enable_animation_part((struct FrameObject *)object,0);
 ((unsigned char *)object)[0xae]=8;
 g_frame_scene_player_slots[player].object=(struct FrameObject *)object;
 if(object->direction>limit)object->oam.flip_x=1;else object->oam.flip_x=0;
 ((struct FrameScenePlayerCollision *)object)->collision=frame_scene_player_collision;
 object->before_step=resource_object_before_step;
 object->actor_state=g_frame_actor_local_need_state;
 ((unsigned char *)object)[0x84]=3;
 frame_update_actor_state((struct FrameObject *)object);
 return (struct FrameObject *)object;
}
asm(".align 2,0");
