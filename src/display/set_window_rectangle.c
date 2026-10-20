#include "display.h"
#include "display_window.h"
void display_set_window_rectangle(unsigned int index, int left, int top, int right, int bottom) {
 struct WindowState *window=&g_window_states[index];
 unsigned int horizontal,vertical;
 union DisplayWindowFixedPoint *position=&window->axes[0].current[0];
 window->axes[0].current[0].position=left;
 position[1].position=top;
 window->axes[1].current[0].position=right;
 window->axes[1].current[1].position=bottom;
 horizontal=((unsigned int)window->axes[0].current[0].halves.integer<<8)|window->axes[1].current[0].halves.integer;
 vertical=((unsigned int)position[1].halves.integer<<8)|(bottom>>16);
 DISPLAY_REG16(0x04000040+index*2)=horizontal;
 DISPLAY_REG16(0x04000044+index*2)=vertical;
}
asm(".align 2, 0");
