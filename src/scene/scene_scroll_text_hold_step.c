#include "scene_scroll_text.h"
void scene_scroll_text_hold_step(struct FrameObject *object){int y=object->position.y;if(y<=0x120000){object->velocity.y=0;g_scene_scroll_text_state.held=object;}else if(y<0x240000){if(g_scene_scroll_text_state.held){g_scene_scroll_text_state.held->flags|=2;g_scene_scroll_text_state.held=0;}}else if(y<=0x200000){if(g_scene_scroll_text_state.held)((struct SceneScrollDisplayFlags *)g_scene_scroll_text_state.held)->control=1;}}
asm(".align 2,0");
