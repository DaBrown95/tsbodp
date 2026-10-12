#include "display.h"
void display_step_backgrounds(void)
{
    unsigned int index;
    struct BackgroundState *background;
    unsigned int duration;
    register unsigned int remaining __asm__("r1");
    unsigned int angle;
    short scale;
    int current;
    int reference;
    register unsigned short *pd_destination __asm__("r3");
    int scaled;
    register unsigned int sample __asm__("r0");
    for (index = 0; index < 4; ++index) {
        background = &g_background_states[index];
        if (!(background->flags & 15))
            continue;
        if (background->flags & 1) {
            sample = background->scroll_duration;
            remaining = sample;
            duration = sample;
            if (remaining) {
                if (remaining == 1) {
                    background->position_x = background->target_x;
                    background->position_y = background->target_y;
                    background->flags &= ~1;
                } else {
                    int delta = background->target_x;
                    current = background->position_x;
                    delta -= current;
                    current += display_divide(delta, *(volatile unsigned short *)&background->scroll_duration);
                    background->position_x = current;
                    delta = background->target_y;
                    current = background->position_y;
                    delta -= current;
                    current += display_divide(delta, *(volatile unsigned short *)&background->scroll_duration);
                    background->position_y = current;
                }
                background->scroll_duration = duration - 1;
            } else
                display_add_point((struct DisplayPoint *)&background->position_x,
                                  (struct DisplayPoint *)&background->velocity_x,
                                  (struct DisplayPoint *)&background->position_x);
            background->flags |= 0x40;
        }
        background->scroll_x = background->position_x;
        background->scroll_y = background->position_y;
        if (background->flags & 0x40)
            display_offset_background(index);
        if (background->flags & 4) {
            background->scale += background->scale_step;
            if (background->scale_step > 0) {
                if (background->scale >= background->maximum_scale) {
                    background->scale = background->maximum_scale;
                    if (background->minimum_scale != background->maximum_scale)
                        background->scale_step = -background->scale_step;
                }
            } else if (background->scale_step < 0) {
                if (background->scale <= background->minimum_scale) {
                    background->scale = background->minimum_scale;
                    if (background->minimum_scale != background->maximum_scale)
                        background->scale_step = -background->scale_step;
                }
            }
            background->flags |= 8;
        }
        if (background->flags & 2) {
            background->angle += background->angle_step;
            background->flags |= 8;
        }
        if (background->flags & 8) {
            angle = background->angle >> 8;
            scale = background->scale;
            background->pa = display_fixed_multiply((short)display_matrix_cosine(angle), scale);
            background->pb = display_fixed_multiply((short)display_matrix_sine(angle), scale);
            background->pc = display_fixed_multiply((short)-display_matrix_sine(angle), scale);
            *(pd_destination = &background->pd) = display_fixed_multiply((short)display_matrix_cosine(angle), scale);
            scaled = (short)background->pa * 120;
            reference = 0x7800;
            reference -= scaled;
            reference -= background->center_x << 8;
            reference -= (short)background->pb * 80;
            background->reference_x = reference;
            scaled = (short)background->pc * 120;
            reference = 0x5000;
            reference -= scaled;
            reference -= background->center_y << 8;
            reference -= *(short *)pd_destination * 80;
            background->reference_y = reference;
            background->flags = (background->flags & ~8) | 0x10;
        }
    }
}
__asm__(".align 2, 0");
