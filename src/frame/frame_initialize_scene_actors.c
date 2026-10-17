#include "frame_scene_actors.h"
void frame_initialize_scene_actors(unsigned int scene) {
 unsigned char direction;
 int x,y;
 int player;
 struct FrameSceneEntrySnapshot *entries;
 struct FrameSceneActorSelection *selection;
 if(g_input_config.player_count<=1){g_input_config.player_count=1;g_input_config.local_player=0;}else g_input_config.local_player=0;
 resource_prepare((const unsigned char *)g_scene_palette_range_configs[scene].unknown_04);
 for(player=0;player<g_input_config.player_count;player++) {
  unsigned char index=player;
  struct FrameObject *object=frame_scene_player_actor(index);
  transition_reset_view(index);
  transition_set_view_mode(0,index);
  transition_configure_view((struct TransitionViewObject *)object,g_transition_view_configuration.point,index);
 }
 resource_spawn_group(0);
 resource_execute_group(0);
 if(g_resource_group_flags&1) {resource_spawn_group(1);resource_execute_group(1);}
 entries=(struct FrameSceneEntrySnapshot *)g_scene_entry_data;
 actor_entry_restore_scene_collection((struct ActorEntryContext *)entries,g_scene_id);
 actor_entry_mark_scene_collection((struct ActorEntryContext *)entries,g_scene_id);
 g_frame_scene_active_actor=frame_create_scene_primary_actor();
 if(entries->world==scene && !entries->exit_flag)frame_create_speed_exit_actor(1,entries->position.x,entries->position.y);
 selection=&g_frame_scene_actor_selection;
 if(selection->world==scene)frame_spawn_saved_scene_effect(selection->position.x,selection->position.y);
 if(selection->actor!=42 && frame_scene_read_spawn(0,&direction,&x,&y)==1 && frame_scene_actor_allowed(selection->actor,scene,(const struct DisplayTimeRecord *)((const unsigned char *)selection+8))==1) {
  struct FrameObject *object=frame_create_actor(selection->actor,direction,x,y);
  transition_object_set_state(object,24);
  frame_set_variant_state(object,2);
 }
}
asm(".align 2,0");
