#include "scene_scroll_text.h"
void scene_scroll_text_step(void){
 unsigned int pressed=g_input_local_pressed[g_input_config.local_player];
 {unsigned int mask=1;mask&=pressed;
 if(mask)scene_scroll_text_confirm();else {unsigned int mask=2;mask&=pressed;
 if(mask)scene_scroll_text_cancel();else {unsigned int mask=192;mask&=pressed;
 if(mask)scene_scroll_text_vertical();else {unsigned int mask=48;mask&=pressed;if(mask)scene_scroll_text_horizontal();}}}}

 scene_scroll_text_update();
}
asm(".align 2,0");
