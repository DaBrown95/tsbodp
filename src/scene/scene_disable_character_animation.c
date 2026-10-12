#include "scene_character_transfer.h"
void scene_disable_character_animation(void) {
 g_scene_character_transfer.flags&=0xfd;
}
