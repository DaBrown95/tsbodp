#include "display_text_helpers.h"
#include "display_text_measure.h"
void frame_set_position(struct FrameObject *, int, int);
void display_position_text_object(struct FrameObject *object, const char *text,
                                  int x, int y, unsigned int flags)
{
    short position_x = x;
    short position_y = y;
    if (flags & 1)
        position_x = (short)position_x - (display_text_measure_width(text) + 1) / 2;
    if (flags & 2)
        position_x = (short)position_x - display_text_measure_width(text);
    if (flags & 4)
        position_y = (short)position_y - (display_text_measure_height(text) + 1) / 2;
    if (flags & 8)
        position_y = (short)position_y - display_text_measure_height(text);
    frame_set_position(object, (unsigned int)position_x << 16,
                       (unsigned int)position_y << 16);
}
asm(".align 2,0");
