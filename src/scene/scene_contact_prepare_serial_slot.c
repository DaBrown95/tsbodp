#include "scene_contact_serial_session_controller.h"

void scene_contact_prepare_serial_slot(unsigned int slot)
{
    struct FrameObject *object = frame_allocate_object(24);
    g_display_scene_frame_objects[slot] = object;
    object->flags = 17;
    object->unknown_0a = slot;
    object->display_palette = slot;
    object->on_step = scene_contact_original_serial_slot_noop;
    frame_set_position(object, g_scene_contact_serial_slot_definitions[slot].x << 16,
                       g_scene_contact_serial_slot_definitions[slot].y << 16);
    frame_set_animation_record(object, &g_scene_contact_serial_slot_definitions[slot].resource);
    if (slot == 2)
        frame_set_animation_commands(object, g_scene_contact_serial_animation_commands, 0);
}
