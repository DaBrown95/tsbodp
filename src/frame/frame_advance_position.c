#include "frame.h"
void frame_advance_position(struct FrameObject *object)
{
    if (object->rate_x) {
        object->phase_x += object->rate_x;
        object->next_position.word.x += frame_cosine(object->phase_x >> 8) * object->amplitude_x;
    }
    if (object->rate_y) {
        object->phase_y += object->rate_y;
        object->next_position.word.y += frame_sine(object->phase_y >> 8) * object->amplitude_y;
    }
}
