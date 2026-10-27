#include "scene_contact_activity_three.h"

#define LINE (&g_scene_contact_activity_three_slots)

void scene_contact_activity_three_original_draw_event(struct FrameObject *base)
{
    struct FramePoint attachment;
    register int observer_x asm("ip");
    int observer_y;
    register int end_x asm("r8");
    register int start_y asm("r5");
    int end_y;
    register int raster_end_y asm("r9");
    register int slope asm("r6");
    int difference_x, difference_y;

    // BUG: attachment.x/y stay unset when observer attachment zero cannot be read.
    scene_contact_activity_three_get_observer_point(&attachment);
    {
        LINE->origin.x = (observer_x = attachment.x);
        observer_y = LINE->origin.y = attachment.y;
        end_x = base->position.x >> 16;
        end_y = base->position.y >> 16;
        if (!(base->flags & 4096)) {
            unsigned int i;
            for (i = 0; i < 16; ++i) {
                if (LINE->objects[i]) {
                    frame_remove_object(LINE->objects[i]);
                    LINE->objects[i] = 0;
                }
            }
            LINE->count = 0;
            return;
        }
        LINE->endpoint.x = end_x;
        LINE->endpoint.y = end_y;
        if ((observer_y >> 16) > end_y) {
            register struct FramePoint swap_observer asm("r5") = {observer_x, observer_y};
            LINE->origin.x = (unsigned int)end_x << 16;
            LINE->origin.y = (unsigned int)end_y << 16;
            LINE->endpoint.x = swap_observer.x >> 16;
            LINE->endpoint.y = swap_observer.y >> 16;
        }
        start_y = LINE->origin.y;
        difference_y = start_y >> 16;
        end_y = LINE->endpoint.y;
        raster_end_y = end_y;
        end_y -= difference_y;
        difference_y = end_y;
        end_x = LINE->origin.x;
        difference_x = LINE->endpoint.x - (end_x >> 16);
        slope = ((int)((unsigned int)difference_x << 21) / difference_y) >> 7;
        LINE->step.x = slope;
        {
            unsigned int orientation = (unsigned int)(slope + 16384);
            unsigned int orientation_limit = 32768;
            int current_y = start_y;
            int current_x = end_x;

            if (orientation > orientation_limit) {
                int step;
                end_y = (int)(((unsigned int)raster_end_y << 22) -
                              ((unsigned int)current_y << 6));
                LINE->horizontal = 1;
                step = (end_y / difference_x) >> 6;
                if (step < 0)
                    step = -step;
                LINE->step.y = step;
                end_y = slope;
                if (current_y < 0) {
                    LINE->origin.x = (unsigned int)current_x +
                        ((unsigned int)end_y << 2) *
                        (unsigned int)((int)(0u - (unsigned int)current_y) >> 16);
                    current_y = 0;
                    LINE->origin.y = current_y;
                }
                LINE->step.x = end_y > 0 ? 65536 : -65536;
            } else {
                register unsigned int vertical_step asm("r1");
                register unsigned char *horizontal asm("r0") = &LINE->horizontal;
                end_y = 0;
                *horizontal = end_y;
                LINE->step.y = 65536;
                vertical_step = (unsigned int)slope << 2;
                LINE->step.x = vertical_step;
                if (start_y < 0) {
                    register unsigned int vertical_offset asm("r0") =
                        0u - (unsigned int)start_y;
                    vertical_offset <<= 16;
                    LINE->origin.x = (unsigned int)end_x + vertical_offset * vertical_step;
                    LINE->origin.y = end_y;
                }
            }
        }
    }
    {
        int advance_x = (unsigned int)LINE->step.x << 3;
        int advance_y, next_x, next_y;
        next_x = (unsigned int)LINE->origin.x + (unsigned int)advance_x;
        LINE->origin.x = next_x;
        advance_y = (unsigned int)LINE->step.y << 3;
        next_y = (unsigned int)LINE->origin.y + (unsigned int)advance_y;
        LINE->origin.y = next_y;
        LINE->endpoint.x = (unsigned int)LINE->endpoint.x - (unsigned int)(advance_x >> 16);
        LINE->endpoint.y = (unsigned int)LINE->endpoint.y - (unsigned int)(advance_y >> 16);
        scene_contact_activity_three_ensure_line_slot(0, next_x, next_y);
    }
    scene_contact_activity_three_raster_line_slot(0);
    scene_contact_activity_three_update_line_slots();
}

__asm__(".align 2,0");
