#include "scene_palette_menu_input.h"
void scene_palette_menu_build_entry_objects(void)
{
    if (g_scene_request.mode != 7) {
        struct FrameObject *first = frame_create_scene_object(129, 273, 11, 1);
        struct FrameObject **objects = g_frame_actor_palette_menu_objects;
        const char *text;
        objects[13] = first;
        objects[13]->flags &= ~1U;
        objects[14] = frame_create_scene_object(128, 272, 12, 1);
        objects[14]->flags &= ~1U;
        objects[8] = frame_create_scene_object(131, 234, 6, 1);
        objects[12] = frame_create_scene_object(130, 274, 13, 1);
        objects[15] = frame_create_scene_object(135, 275, 14, 1);
        objects[16] = frame_create_scene_object(136, 276, 14, 1);
        display_text_select_font(3, 0, 0);
        text = display_scene_lookup_text(50);
        objects[11] = display_scene_create_label(133, &text);
        transition_object_set_state(objects[11], 14);
        text = display_scene_lookup_text(51);
        objects[10] = display_scene_create_label(132, &text);
        transition_object_set_state(objects[10], 14);
        g_scene_request.scene = 0;
    } else {
        unsigned char i;
        struct FrameObject *object;
        for (i = 0; i < g_frame_actor_palette_menu_exit_count; ++i) {
            object = g_frame_actor_palette_menu_exit_objects[i];
            object->on_step = frame_scene_object_tick;
            transition_object_set_state(object, 14);
            ((struct FrameActorObject *)object)->need_timer = 18;
            frame_begin_position_move(object, object->position.x, 37 * 65536, 19);
            frame_step_position_move(object);
            frame_set_variant_state(object, 3);
        }
        {
            struct FrameObject *last = g_frame_actor_palette_menu_objects[7];
            if (last)
                last->flags = (last->flags & ~1U) | 2;
        }
        g_scene_request.scene = 3;
    }
}
asm(".align 2,0");
