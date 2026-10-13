#include "frame_scene_player.h"
struct FrameSceneSavedEffect *frame_spawn_saved_scene_effect(int x,int y) {
 struct FrameSceneSavedEffect *effect=frame_create_scene_saved_effect(g_frame_scene_actor_selection.saved_effect_kind,x,y);
 if(effect) {
  effect->owner=g_frame_scene_player_slots[0].object;
  effect->value=g_frame_scene_actor_selection.saved_effect_value;
 }
 return effect;
}
