#include "scene_scroll_text.h"
void scene_scroll_text_end_step(struct FrameObject *object){
 int y=object->position.y;
 if(y<0){object->flags|=2;if(g_scene_previous_request.unknown_00==6)resource_submit_scene(6,0,g_scene_request.scene);else scene_submit_default_request(5);}
 else if(y<0x240000){object->flags&=~1U;if(g_scene_scroll_text_state.held){g_scene_scroll_text_state.held->flags|=2;g_scene_scroll_text_state.held=0;}}
 else if(y<0x200000){((struct SceneScrollDisplayFlags *)object)->control=1;
 if(g_scene_scroll_text_state.held)((struct SceneScrollDisplayFlags *)g_scene_scroll_text_state.held)->control=1;}
}
asm(".align 2,0");
