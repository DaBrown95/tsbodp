/* Partial scene-request/state layouts inferred from the connected load sequence. */
#include "display.h"
#include "display_object_palette.h"
#include "display_time.h"
struct PaletteRangeConfig;
#include "scene_request.h"
#include "scene_retention.h"
#include "frame_scene_actor_schedule.h"
struct SceneContext { unsigned int flags, period; unsigned int unknown_08; void *palette; };
struct SceneModeFlags { unsigned int unknown_00, flags; };
struct ScenePaletteRangeConfig { const struct PaletteRangeConfig *resource; unsigned int unknown_04, unknown_08; };
extern struct SceneContext g_scene_context;
extern struct SceneModeFlags g_scene_mode_flags;
extern unsigned int g_scene_id, g_palette_range_enabled_mask;
extern unsigned short g_scene_palette_indices[4];
extern unsigned char g_scene_mode_bytes[4], g_scene_world_state[], g_scene_entry_data[];
extern const unsigned int g_scene_background_control0, g_scene_background_control1, g_scene_background_control2;
extern struct ScenePaletteRangeConfig g_scene_palette_range_configs[];
#include "audio_vblank.h"
extern void scene_vblank_callback(void), set_vblank_callback(void (*)(void));
extern void scene_stage_0803e3a8(void), scene_prepare_load(void);
extern void *scene_palette_source(void);
extern void display_load_palette(const void *, unsigned int, unsigned int);
extern void frame_load_scene_map_resources(unsigned int), frame_reset_scene_actor_schedule(void), frame_initialize_scene_actors(unsigned int), scene_stage_08037444(void);
extern void display_configure_tile_allocation(unsigned char), display_reset_tile_allocation(void);
extern void scene_clear_shared_display(void), frame_reset_primary_display_indices(void);
extern void scene_copy_palette_alternate(const void *, unsigned int, unsigned int), scene_resume_actor_speed_cue(void);
extern unsigned char scene_audio_for_period(unsigned int);
extern void audio_select_sequence(unsigned char), scene_initialize_objects(void *, unsigned int), scene_initialize_transient_slots(void), display_load_palette_ranges(const struct PaletteRangeConfig *);
extern void scene_initialize_view(unsigned int, unsigned int), scene_update_view(unsigned int), scene_show_view(unsigned char), scene_stage_0800e3a8(unsigned char);
extern void display_set_mode(unsigned short), display_show_background(unsigned int, unsigned int), display_enable_layers(unsigned short);
extern void display_cpu_copy(const void *, void *, unsigned int);
extern void transition_fade_black_in_record(unsigned short), transition_run_first(unsigned short, unsigned int);
