#include "display.h"
void display_disable_layers(unsigned short mask)
{
    g_display_control.control &= ~mask;
    g_display_control.flags |= 2;
}
