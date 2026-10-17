#include "irq.h"
#include "transition_mosaic.h"

void transition_fade_black_in_windows(unsigned short targets)
{
    int level;

    REG16(0x04000048) = 0;
    REG16(0x0400004A) = 0x1F;
    REG16(0x04000040) = 0xF0;
    REG16(0x04000044) = 0x20;
    REG16(0x04000042) = 0xF0;
    REG16(0x04000046) = 0x80A0;
    REG16(0x04000000) |= 0x6000;
    REG16(0x04000050) = targets | 0xC0;

    for (level = 16; level >= 0; --level) {
        REG16(0x04000054) = level;
        frame_request_refresh();
        display_step_backgrounds();
        display_step_palette_jobs();
        frame_prepare_oam_transfer();
        irq_wait_vblank();
        irq_wait_vblank();
    }
}
