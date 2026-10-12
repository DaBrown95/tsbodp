#include "display_scene_lifecycle.h"
struct FrameObject *display_scene_create_label(unsigned int id, const char **text)
{
    struct FrameObject *object = display_allocate_text_object(text);
    object->on_step = frame_scene_object_tick;
    object->unknown_0a = 0x13b;
    object->id = id;
    frame_set_variant_state(object, 0);
    frame_set_centered_integer_position(object, g_frame_scene_positions[id].x0,
                                        g_frame_scene_positions[id].y0);
    return object;
}
