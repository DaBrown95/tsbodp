#ifndef SCENE_CHOICE_PANEL_H
#define SCENE_CHOICE_PANEL_H
#include "frame.h"
#include "frame_actor_scene.h"
#include "scene_request.h"
#include "scene_retention.h"
#include "display_catalog_text.h"
#include "display_text_raster.h"
#include "heap.h"
#include "audio_game.h"

/* Byte consumers of the existing request word; no second struct owner. */
#define SCENE_CHOICE_PANEL_COUNT (((unsigned char *)&g_actor_scene_request.unknown_00)[0])
#define SCENE_CHOICE_PANEL_X (((unsigned char *)&g_actor_scene_request.unknown_00)[1])
#define SCENE_CHOICE_PANEL_Y (((unsigned char *)&g_actor_scene_request.unknown_00)[2])
#define SCENE_CHOICE_PANEL_FLAGS (((unsigned char *)&g_actor_scene_request.unknown_00)[3])

/* Observed width/height bytes; this is not a claim about surrounding storage. */
struct SceneChoicePanelSize { unsigned char width, height; };
extern struct SceneChoicePanelSize g_scene_choice_panel_size;
/* Five observed ID slots, also cleared as a ten-byte prefix. */
extern unsigned short g_need_effect_choice_text[5];

void scene_choice_panel_initialize(void);
void scene_choice_panel_shutdown(void);
void scene_choice_panel_begin_close(void);

/* Remaining phase and drawing bodies are original ROM services. */
void scene_choice_panel_step_original(void);
void scene_choice_panel_draw_text_original(void);
void scene_choice_panel_original_window_begin(unsigned short duration);
void scene_choice_panel_original_window_end(unsigned short duration);
void scene_choice_panel_original_disable_windows(void);
void scene_choice_panel_original_configure_windows(unsigned short inside0,
 unsigned short inside1, unsigned short outside);
void scene_choice_panel_original_set_window(int left, int top, int right, int bottom);

/* Existing compatible providers; their owning headers are kept separate. */
void frame_set_position(struct FrameObject *, int, int);
int display_bios_remainder(int, int);
unsigned int scene_queued_request_kind(void);
void transition_run_second(unsigned short, unsigned int);
void scene_retain_display(void);
void frame_clear_transient_effects(void), frame_clear_render_effects(void);
void frame_configure_deferred_display(unsigned char);
void display_reset_palette_jobs(void), display_reset(void);
void set_vblank_callback(void (*)(void)), irq_default_vblank_callback(void);
#endif
