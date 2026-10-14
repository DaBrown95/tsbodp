#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
unsigned int scene_contact_activity_three_get_value(unsigned int selector) {
 unsigned char *value;
 if(selector==2)value=&STATE->values[2];
 else if(selector==1)value=&STATE->values[1];
 else value=&STATE->values[0];
 return *value;
}
asm(".align 2,0");
