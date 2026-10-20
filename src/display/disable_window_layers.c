#include "display_window.h"
void display_disable_window_layers(void)
{
 display_disable_layers(0x6000);
}
asm(".align 2,0");
