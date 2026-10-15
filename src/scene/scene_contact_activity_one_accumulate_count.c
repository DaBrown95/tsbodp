#include "scene_contact_activity_one.h"
#define STATE ((struct SceneContactActivityOneState*)g_scene_contact_state)
void scene_contact_activity_one_accumulate_count(unsigned int count,unsigned int value) {
 unsigned int i;for(i=0;i<count;++i)STATE->score+=value>>i;
}
asm(".align 2,0");
