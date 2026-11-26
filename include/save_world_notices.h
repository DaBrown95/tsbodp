#ifndef SAVE_WORLD_NOTICES_H
#define SAVE_WORLD_NOTICES_H
#include "frame_actor_scene.h"
#include "frame_actor_actions.h"
#include "display_text_measure.h"
#include "display_catalog_text.h"
#include "audio_game.h"

void save_world_show_row_notice(unsigned int);
void save_world_show_row_flag_notice(unsigned int);
/* The complete incoming word is retained until its halfword result store. */
void save_world_show_notice(unsigned int);
void scene_submit_default_request(unsigned int);

/* Reuse the observed notification overlay; no complete request layout is claimed. */
#if TSBO_REVISION == 0
static inline void save_world_center_notice(void)
{
    unsigned char width, height;
    width = display_text_measure_width(display_scene_lookup_text(g_actor_scene_result_id.id));
    height = display_text_measure_height(display_scene_lookup_text(g_actor_scene_result_id.id));
    ((struct FrameActorParameterNotification *)&g_actor_scene_request)->active = 0;
    ((struct FrameActorParameterNotification *)&g_actor_scene_request)->x = (30 - (width >> 3)) / 2;
    ((struct FrameActorParameterNotification *)&g_actor_scene_request)->y = 7 - (height >> 4);
    scene_submit_default_request(2);
}
#else
/* Revision 1 restores the notice font after measuring. Its code matches an
 * expansion in each caller rather than an inlined call. */
void display_text_select_font(unsigned int, int, int);
#define save_world_center_notice()                                                                 \
    do {                                                                                           \
        unsigned char width, height;                                                               \
        width = display_text_measure_width(display_scene_lookup_text(g_actor_scene_result_id.id)); \
        height =                                                                                   \
            display_text_measure_height(display_scene_lookup_text(g_actor_scene_result_id.id));    \
        display_text_select_font(3, 0, -1);                                                        \
        ((struct FrameActorParameterNotification *)&g_actor_scene_request)->active = 0;            \
        ((struct FrameActorParameterNotification *)&g_actor_scene_request)->x =                    \
            (30 - (width >> 3)) / 2;                                                               \
        ((struct FrameActorParameterNotification *)&g_actor_scene_request)->y = 7 - (height >> 4); \
        scene_submit_default_request(2);                                                           \
    } while (0)
#endif
#endif
