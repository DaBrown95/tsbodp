#include "scene_choice_panel.h"
#include "display.h"
#include "display_window.h"

struct WindowPackWords {
 int right;
 unsigned int horizontal;
};
typedef char WindowPackWordsLayout[
 (sizeof(struct WindowPackWords)==8 && __alignof__(struct WindowPackWords)==4) ? 1 : -1];
void scene_choice_panel_original_set_window(int left,int top,int right,int bottom)
{
 register int left_input asm("r0")=left;
 register int top_input asm("r1")=top;
 struct WindowState *windows=g_window_states;
 union DisplayWindowFixedPoint *position=&windows[1].axes[0].current[0];
 register struct WindowPackWords pack asm("r0");
 register unsigned int horizontal asm("r1");
 unsigned int vertical;
 windows[1].axes[0].current[0].position=left_input;
 position[1].position=top_input;
 windows[1].axes[1].current[0].position=right;
 windows[1].axes[1].current[1].position=bottom;
 horizontal=*(volatile int *)&windows[1].axes[0].current[0].position;
 pack.horizontal=horizontal;
 pack.horizontal=(unsigned int)((int)pack.horizontal>>16);
 pack.horizontal<<=8;
 pack.right=right;
 pack.right>>=16;
 pack.horizontal|=(unsigned int)pack.right;
 horizontal=pack.horizontal;
 vertical=((unsigned int)position[1].halves.integer<<8)|(bottom>>16);
 DISPLAY_REG16(0x04000042)=horizontal;
 DISPLAY_REG16(0x04000046)=vertical;
 display_enable_layers(0x4000);
}
asm(".align 2,0");
