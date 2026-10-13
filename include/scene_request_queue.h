#ifndef SCENE_REQUEST_QUEUE_H
#define SCENE_REQUEST_QUEUE_H
#include "scene_request.h"
#include "irq.h"
#include "save_stream.h"

/* Three 24-byte request views; names follow the observed copy order. */
extern struct SceneRequest g_scene_previous_request, g_scene_queued_request;
typedef void (*ScenePhaseCallback)(void);
struct ScenePhaseCallbacks { ScenePhaseCallback begin, step, end; };
extern const struct ScenePhaseCallbacks g_scene_phase_callbacks[];
extern unsigned int g_game_flags, g_frame_allocation_epoch;

void resource_submit_scene(unsigned int, unsigned int, unsigned int);
void scene_submit_default_request(unsigned int);
unsigned int scene_current_request_kind(void), scene_queued_request_kind(void);
unsigned char scene_request_changed(void);
void scene_run_begin_callback(void), scene_run_step_callback(void);
void scene_run_end_callback(void), scene_initialize_request_queue(void);
void scene_step_request_handoff(void);
void input_poll(void), display_step_backgrounds(void);
unsigned char frame_request_refresh(void);
void frame_prepare_oam_transfer(void);
/* Original providers remain explicit. */
int transition_link_update(void);
void scene_allocate_retained_palette(void);
void scene_update_windows_080489c4(void), transition_palette_update_080117d4(void);
#endif
