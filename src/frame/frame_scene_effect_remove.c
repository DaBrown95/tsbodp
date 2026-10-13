#include "frame_scene_player.h"
static inline unsigned char is_player_effect(struct FrameSceneSavedEffect *effect) { if(effect->owner==g_frame_scene_player_slots[0].object) return 1; return 0; }
void frame_scene_effect_remove(struct FrameObject *object) {
 struct FrameSceneSavedEffect *effect=(struct FrameSceneSavedEffect *)object;
 unsigned char same=is_player_effect(effect);
 if(same) {
  if(g_frame_scene_actor_selection.world!=50) {
   g_frame_scene_actor_selection.position=object->position;
   g_frame_scene_actor_selection.world=g_frame_world_id;
   g_frame_scene_actor_selection.saved_effect_kind=((struct FrameActorObject *)object)->actor_id;
  }
 }
}
