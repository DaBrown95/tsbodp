#include "scene_phase25.h"
#include "frame_scene_motion.h"
#include "frame_transient_effect.h"
#include "display_scene_lifecycle.h"
#include "scene_request_queue.h"
#include "scene_map_selection.h"
#include "input.h"
#include "audio_game.h"

void scene_phase25_step(void)
{
    frame_step_transient_effects();
    switch (g_scene_request.unknown_10) {
    case 0:
        if (g_input_pressed[g_input_config.local_player] & 1) {
            transition_run_second(63, 0);
            scene_phase25_initialize_objects();
            audio_play_animation_cue(180);
            g_scene_request.unknown_10 = 1;
        }
        break;
    case 1:
        if (((struct FrameActorObject *)g_display_scene_frame_objects[0])->variant_state == 11) {
            g_scene_request.unknown_10 = 2;
            g_scene_request.unknown_14 = 0;
        }
        break;
    case 2:
        {
            struct SceneRequest *request = &g_scene_request;
            unsigned int timer = request->unknown_14;
            if (timer == 20) {
                g_display_scene_frame_objects[1]->flags |= 1;
            } else if (timer == 30) {
                struct FrameObject **objects = g_display_scene_frame_objects;
                ((struct FrameActorObject *)objects[0])->need_timer = timer;
                frame_begin_position_move(objects[0], 320 * 65536, 144 * 65536,
                    ((struct FrameActorObject *)objects[0])->need_timer);
                frame_set_variant_state(objects[0], 3);
                request->unknown_10 = 3;
                request->unknown_14 = 0;
            }
        }
        break;
    case 3:
        if (((struct FrameActorObject *)g_display_scene_frame_objects[0])->variant_state == 11)
            g_scene_request.unknown_10 = 4;
        break;
    case 4:
        resource_submit_scene(1, 4, 6);
        break;
    }
    ++g_scene_request.unknown_14;
}

asm(".align 2, 0");
