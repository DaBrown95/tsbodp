#include "scene_palette_menu_entry.h"

/* Access view of the existing aligned halfword field, not new storage. */
struct PaletteTimerCell {
    unsigned short value;
} __attribute__((packed, aligned(2)));

void scene_palette_menu_phase_0(void)
{
    unsigned int phase = g_scene_request.unknown_10;
    if (!phase) {
        unsigned int timer = g_scene_request.unknown_14;
        if (timer == 30) {
            struct FrameObject **objects;
            display_set_window_rectangle(1, 0, 160 * 65536, 240 * 65536,
                                         160 * 65536);
            display_configure_window(1, 63, 60);
            display_set_background_scroll_target(1, 0, 0, 15);
            display_set_background_scroll_target(0, 0, 0, 15);
            display_begin_window_axis_move(1, 0, 0, 0, 15);
            display_enable_background(1);
            display_enable_background(0);
            objects = g_frame_actor_palette_menu_objects;
            objects[13]->id = 129;
            objects[14]->id = 128;
            if (g_scene_request.scene != 3) {
                objects[13]->flags |= 1;
                ((struct FrameActorObject *)objects[13])->need_timer = 16;
                frame_set_variant_state(objects[13], 56);
                objects[14]->flags &= ~1U;
                frame_set_variant_state(objects[14], 58);
            } else {
                objects[13]->flags &= ~1U;
                frame_set_variant_state(objects[13], 58);
                objects[14]->flags |= 1;
                ((struct FrameActorObject *)objects[14])->need_timer = 16;
                frame_set_variant_state(objects[14], 56);
            }
            objects = g_frame_actor_palette_menu_objects;
            objects[8]->id = 131;
            ((struct FrameActorObject *)objects[8])->need_timer = 14;
            frame_set_variant_state(objects[8], 56);
            objects[12]->id = 130;
            ((struct FrameActorObject *)objects[12])->need_timer = 16;
            frame_set_variant_state(objects[12], 56);
            objects[15]->id = 135;
            {
                struct PaletteTimerCell *destination = (struct PaletteTimerCell *)
                    &((struct FrameActorObject *)objects[15])->need_timer;
                destination->value = (timer = 15);
            }
            frame_set_variant_state(objects[15], 56);
            objects[16]->id = 136;
            ((struct FrameActorObject *)objects[16])->need_timer = timer;
            frame_set_variant_state(objects[16], 56);
            objects[10]->id = 132;
            ((struct FrameActorObject *)objects[10])->need_timer = timer;
            frame_set_variant_state(objects[10], 56);
        } else if (timer == 15) {
            struct FrameObject **objects;
            display_configure_window(1, 63, 59);
            display_set_window_rectangle(1, 0, 0, 240 * 65536, phase);
            display_set_background_scroll_target(2, 0, 0, 15);
            display_begin_window_axis_move(1, 1, 240 * 65536, 176 * 65536, timer);
            display_enable_background(2);
            g_scene_request.parameter = phase;
            display_enable_background(1);
            display_enable_background(0);
            objects = g_frame_actor_palette_menu_objects;
            objects[11]->id = 133;
            ((struct FrameActorObject *)objects[11])->need_timer = timer;
            frame_set_variant_state(objects[11], 56);
        } else if (timer == 1) {
            display_disable_window(1);
        } else if (timer == 0) {
            g_scene_request.unknown_10 = 1;
        } else if (timer == 31) {
            scene_palette_menu_prepare_entry();
            audio_play_animation_cue(12);
        }
        --g_scene_request.unknown_14;
    }
}

asm(".align 2,0");
