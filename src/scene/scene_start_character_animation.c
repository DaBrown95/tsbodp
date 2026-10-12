#include "scene_character_transfer.h"
void scene_start_character_animation(struct SceneCharacterTransferResource *resource,struct BackgroundState *background) {
 g_scene_character_transfer.flags=3;
 g_scene_character_transfer.frame=0;
 g_scene_character_transfer.elapsed=0;
 g_scene_character_transfer.resource=resource;
 g_scene_character_transfer.background=background;
}
