#include "scene_scroll_text.h"
void scene_scroll_text_update(void){if(!g_scene_scroll_text_state.stopped){struct FrameObject *latest=g_scene_scroll_text_state.latest;if(!latest||latest->position.y<0xa00000)scene_scroll_text_append();}{struct SceneScrollTextState *state=&g_scene_scroll_text_state;int total;{register unsigned short increment asm("r0");increment=-1;total=increment;}total+=(unsigned short)state->y;state->y=total;}}
asm(".align 2,0");
