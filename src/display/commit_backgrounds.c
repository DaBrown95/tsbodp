#include "display.h"

void display_commit_backgrounds(void)
{
    unsigned int i;
    register volatile unsigned short *scroll_x __asm__("r6");
    register int reference_mask __asm__("r5");
    unsigned int scroll_offset;
    struct BackgroundState *background;
    volatile unsigned short *affine;
    int value;
    i = 0;
    reference_mask = 0x0fff0000;
    scroll_x = (volatile unsigned short *)0x04000010;
    for (; i < 4; ++i) {
        background = &g_background_states[i];
        if (background->flags & 0x70) {
            if ((background->flags & 0x50) && g_display_commit_context->commit_pending) {
                if (background->flags & 0x10) {
                    if (i == 2)
                        affine = (volatile unsigned short *)0x04000020;
                    else if (i == 3)
                        affine = (volatile unsigned short *)0x04000030;
                    else
                        goto scroll;
                    *affine++ = background->pa;
                    *affine++ = background->pb;
                    *affine++ = background->pc;
                    *affine++ = background->pd;
                    value = background->reference_x;
                    *affine++ = value;
                    *affine++ = (value & reference_mask) >> 16;
                    value = background->reference_y;
                    *affine++ = value;
                    *affine = (value & reference_mask) >> 16;
                }
scroll:
                if (background->flags & 0x40) {
                    scroll_offset = i * 4;
                    *scroll_x = background->scroll_x >> 16;
                    scroll_offset += 0x04000012;
                    *(volatile unsigned short *)scroll_offset = background->scroll_y >> 16;
                }
                background->flags &= ~0x50;
            }
            if (background->flags & 0x20) {
                background->flags &= ~0x20;
                DISPLAY_REG16(0x04000008 + i * 2) = background->registers.control;
            }
            if ((background->flags & 0x30) == 0x30) {
                background->flags &= ~0x20;
                display_cpu_copy(background->tilemap_source, background->tilemap_destination, 0x400);
            }
        }
        scroll_x += 2;
    }
    if (g_display_control.flags & 2) {
        g_display_control.flags &= ~2;
        DISPLAY_REG16(0x04000000) = (DISPLAY_REG16(0x04000000) & 0x80) | g_display_control.control;
    }
}
