#include "scene_scroll_text.h"
void scene_scroll_text_append(void){
 const char *text=display_scene_lookup_text(g_scene_request.parameter);int kind=-1;
 if(*text=='^'){const char *digits=text+1;text=digits;if((unsigned char)(*digits-'0')<=9){kind=*digits-'0';text=digits+1;}}
 {unsigned int font=1;if(kind==1)font=3;display_text_select_font(font,3,0);}
 if(*text){struct FrameObject *object=display_allocate_text_object(&text);
 frame_set_centered_integer_position(object,g_scene_scroll_text_state.x,g_scene_scroll_text_state.y);object->velocity.y=-65536;
 if(kind==0){g_scene_scroll_text_state.stopped=1;object->on_step=scene_scroll_text_end_step;}
 else if(kind==1)object->on_step=scene_scroll_text_hold_step;else object->on_step=scene_scroll_text_regular_step;
 g_scene_scroll_text_state.latest=object;}
 g_scene_scroll_text_state.y+=12;++g_scene_request.parameter;
}

asm(".align 2,0");
