#include "scene_character_transfer.h"
void scene_commit_character_transfer(void) {
 if(g_scene_character_transfer.flags&4) {
  struct SceneCharacterTransferRecord *record;
  g_scene_character_transfer.flags&=0xfb;
  record=&g_scene_character_transfer.resource->records[g_scene_character_transfer.frame];
  DISPLAY_DMA3->source=(unsigned int)record->source;
  DISPLAY_DMA3->destination=0x06000000 + (((struct SceneCharacterBase *)g_scene_character_transfer.background)->character_base<<14);
  DISPLAY_DMA3->control=(record->bytes>>1)|0x80000000;
  (void)DISPLAY_DMA3->control;
 }
}
