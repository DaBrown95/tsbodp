#include "display_scene_lifecycle.h"
void display_scene_clear_detail_background(void)
{
    display_fill_background(0, 0);
}
/* Zero-filled alignment after the pool-free Thumb function. */
__asm__(".align 2, 0");
