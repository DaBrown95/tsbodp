#ifndef SCENE_CONTACT_ACTIVITY_TWO_H
#define SCENE_CONTACT_ACTIVITY_TWO_H
#include "frame_actor_runtime.h"
#include "resource_transition.h"
#include "frame_random.h"
#include "audio_game.h"
#include "display.h"
#include "display_time_hud.h"
#include "display_text_fields.h"
#include "scene_contact_activity.h"
#include "view_math.h"

/* Observed row-two 96-byte prefix within the 420-byte scene allocation. */
struct SceneContactState;
extern struct SceneContactState *g_scene_contact_state;
struct SceneContactActivityTwoEntry {
 struct FrameObject *object;
 unsigned char position, variant, unknown06[2];
};
struct SceneContactActivityTwoState {
 unsigned char unknown00[10];
 unsigned short event_hits;
 short score;
 unsigned short selected_row;
 unsigned char unknown10[3], option, phase, flags, unknown16[2];
 struct SceneContactActivityTwoEntry entries[7];
 struct FrameObject *primary, *secondary, *event;
 unsigned int sound_handle;
};
/* Whole-object-rooted observed 216-byte prefixes; the allocator reserves 320. */
struct SceneContactActivityTwoObject {
 unsigned char unknown00[8];unsigned short id, subtype;unsigned int flags;
 unsigned char unknown10[0xc1];
 unsigned char mode:2, contact_mode:2, unknown_d1_4:1, double_size:1, unknown_d1_6:2;
 unsigned char unknown_d2_d4[3];
 unsigned char tile_high:2, layer:2, palette:4;
};
struct SceneContactActivityTwoRowObject {
 unsigned char unknown00[8];unsigned short id, subtype;unsigned int flags;
 unsigned char unknown10[0x3d], state, phase, pending_updates, unknown50[8];
 unsigned int timer;unsigned char unknown5c[44];
 void (*on_step)(struct FrameObject *);
 unsigned char unknown8c[0x45];
 unsigned char mode:2, contact_mode:2, unknown_d1_4:1, double_size:1, unknown_d1_6:2;
 unsigned char unknown_d2_d4[3];
 unsigned char tile_high:2, layer:2, palette:4;
};
/* Seven 88-byte rows are observed before the separate 60-byte resource table. */
struct SceneContactActivityTwoRow {
 struct FramePoint positions[3];
 struct FrameVariantResource animation_hit, animation, animation_result;
 const void *palette;
 int x, y;
 unsigned char weight, unknown55[3];
};
struct SceneContactActivityTwoEventResource {
 const struct BackgroundResource *resource;
 struct FrameVariantResource animation, animation_finish, animation_miss;
 const void *palette;
 unsigned char character_base, palette_slot, map_palette, unknown3b;
};
struct SceneContactActivityTwoScore {
 unsigned char initial, base_reward, unknown02[2];
};
extern struct SceneContactActivityTwoRow g_scene_contact_activity_two_rows[];
extern struct SceneContactActivityTwoEventResource g_scene_contact_activity_two_event_resources[];
extern const struct SceneContactActivityTwoScore g_scene_contact_activity_two_scores[];
extern const unsigned char g_scene_contact_activity_two_rates[3][3];
extern const unsigned char g_scene_contact_activity_two_reflections[];
extern struct FramePoint g_view_direction_vectors[];
extern struct FrameVariantResource g_scene_contact_activity_two_primary_animation;
extern struct FrameVariantResource g_scene_contact_activity_two_secondary_animation;
extern unsigned char g_scene_contact_activity_two_primary_program[], g_scene_contact_activity_two_secondary_program[];
extern const struct DisplayTimeRecord g_scene_contact_activity_two_clock;
extern const struct BackgroundResource g_scene_contact_activity_two_background3, g_scene_contact_activity_two_background1;
extern const unsigned int g_scene_contact_activity_four_background1, g_scene_contact_activity_four_background2;
extern const unsigned int g_scene_contact_initial_background_control1;

void scene_contact_activity_two_initialize(void);
void scene_contact_activity_two_step(void);
struct FrameObject *scene_contact_activity_two_create_primary(void);
struct FrameObject *scene_contact_activity_two_create_secondary(void);
struct FrameObject *scene_contact_activity_two_create_row(unsigned int);
struct FrameObject *scene_contact_activity_two_create_event(unsigned int);
void scene_contact_activity_two_step_row(struct FrameObject *);
void scene_contact_activity_two_step_event(struct FrameObject *);
void scene_contact_activity_two_step_completed_event(struct FrameObject *);
void scene_contact_activity_two_step_row_result(struct FrameObject *);
void scene_contact_activity_two_draw_row(unsigned int);
void scene_contact_activity_two_draw_score(void);
void scene_contact_activity_two_reset_controls(void);
void scene_contact_activity_two_begin_transfer(unsigned int, unsigned char);
/* Current accepted provider contracts; these declarations add no coverage. */
void display_show_background(unsigned int,unsigned int);
void display_fill_background(unsigned int,unsigned short);
const unsigned short *display_load_background(unsigned int,const struct BackgroundResource *,unsigned short,unsigned short,unsigned int,unsigned int);
void display_set_background_rectangle_palette(unsigned int,int,int,int,int,unsigned short);
void scene_contact_add_activity_score(int);
void frame_set_animation_frame(struct FrameTickObject *, unsigned char);
#endif
