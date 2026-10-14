#include "scene_contact_activity_three.h"
union SceneContactActivityThreeValueStateView {struct SceneContactActivityThreeState fields;struct {unsigned char prefix00[88];unsigned int value_word;} value;};
void scene_contact_activity_three_decrement_value(unsigned int selector) {
 struct SceneContactState **root;
 union SceneContactActivityThreeValueStateView *state;
 register unsigned char *value asm("r1");
 if(selector==2)value=&((union SceneContactActivityThreeValueStateView*)*(root=&g_scene_contact_state))->fields.values[2];
 else if(selector==1)value=&((union SceneContactActivityThreeValueStateView*)*(root=&g_scene_contact_state))->fields.values[1];
 else value=&((union SceneContactActivityThreeValueStateView*)*(root=&g_scene_contact_state))->fields.values[0];
 --*value;
 state=(union SceneContactActivityThreeValueStateView*)*root;
 if(!(state->value.value_word&0x00ffffffu))state->fields.flags|=1;
 scene_contact_activity_three_refresh_value(g_scene_contact_activity_three_control.selection.bytes[0],g_scene_contact_activity_three_control.selection.bytes[0]);
}
asm(".align 2,0");
