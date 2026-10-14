#include "scene_text_bank.h"
void scene_text_bank_load_preview(unsigned int bank)
{
    display_load_background_dma(3, g_scene_text_bank_backgrounds[bank],
                                1, 1, 0, 0);
}
asm(".align 2,0");
