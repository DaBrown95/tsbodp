#include "scene_character_transfer.h"
void scene_step_character_animation(void) {
 if(g_scene_character_transfer.flags==3) {
  g_scene_character_transfer.elapsed++;
  if(g_scene_character_transfer.elapsed>=g_scene_character_transfer.resource->records[g_scene_character_transfer.frame].duration) {
   g_scene_character_transfer.elapsed=0;
   g_scene_character_transfer.frame++;
   if(g_scene_character_transfer.frame>=g_scene_character_transfer.resource->count)
    g_scene_character_transfer.frame=0;
   g_scene_character_transfer.flags|=4;
  }
 }
}
