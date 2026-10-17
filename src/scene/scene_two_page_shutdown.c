#include "transition.h"

void scene_two_page_shutdown(void)
{
    transition_set_black_brightness(63, 16);
    display_reset_palette_jobs();
}

/* Original two zero alignment bytes, outside the eighteen-byte C body. */
asm(".align 2,0");
