#ifndef SCENE_CONTACT_ACTIVITY_SIX_H
#define SCENE_CONTACT_ACTIVITY_SIX_H
#include "frame_actor_runtime.h"
#include "resource_transition.h"
#include "frame_random.h"
#include "display.h"
#include "audio_game.h"
#include "audio_game_activity.h"
#include "input.h"
extern const unsigned short g_scene_contact_activity_six_success_palette[],g_scene_contact_activity_six_failure_palette[];
void scene_contact_activity_six_set_channel_pair_volume(unsigned int);
void scene_contact_activity_six_remove_finished(struct FrameObject*);
unsigned int audio_game_get_channel_volume(unsigned int);
void audio_game_set_channel_volume(unsigned int,unsigned int);
int save_world_scale_percent(int,unsigned short);
int save_world_ratio_percent(int,int);
void frame_set_animation_frame(struct FrameTickObject*,unsigned char);
void scene_contact_add_activity_score(int);
void frame_enable_object_flags(struct FrameObject*,unsigned int);
struct SceneContactState;
extern struct SceneContactState *g_scene_contact_state;
/* Observed 48-byte access prefix inside the 420-byte scene allocation. */
struct SceneContactActivitySixState {
 struct FrameObject *primary;
 unsigned char unknown04[8];
 short amount;unsigned short failures;
 unsigned char unknown10[3],option,phase,flags,unknown16[2];
 struct FrameObject *secondary,*first,*second,*gauge;
 short palette_timer;unsigned char events,saved_sequence_volume,saved_sample_volume;
};
struct SceneContactActivitySixOption {
 int speed;unsigned char first_threshold,second_threshold,third_threshold,failure_threshold,reward,sequence,unknown0a[2];
};
struct SceneContactActivitySixNoticeObject {unsigned char unknown00[0x58];unsigned int notice_parameter;};
/* Whole-object access prefix, 216 bytes/alignment4. D1 bits2..3 are
 * cleared by these factories; bit4 is retained. Allocation is320 bytes. */
struct SceneContactActivitySixObject {
 unsigned char unknown00[8];unsigned short id,subtype;unsigned int flags;
 unsigned char unknown10[0xc1];
 unsigned char mode:2,contact_mode:2,unknown_d1_4:1,double_size:1,unknown_d1_6:2;
 unsigned char unknown_d2;unsigned char unknown_d3_low:4,secondary:1,unknown_d3_high:3;unsigned char unknown_d4;
 unsigned char tile_high:2,layer:2,palette:4;
};
/* Five option records are observed; unchecked selectors have no new guard. */
extern const struct SceneContactActivitySixOption g_scene_contact_activity_six_options[];
extern struct FrameVariantResource g_scene_contact_activity_six_first_animations[],g_scene_contact_activity_six_second_animations[],g_scene_contact_activity_six_gauge_animations[];
extern const unsigned int g_scene_contact_initial_background_control1,g_scene_contact_activity_four_background2,g_scene_contact_activity_four_background1;
extern const struct BackgroundResource g_scene_contact_activity_six_background3,g_scene_contact_activity_six_background2,g_scene_contact_activity_six_background1;
extern const struct PaletteRangeConfig g_scene_contact_activity_six_palette_ranges;
extern const void *const g_scene_contact_activity_six_palette2[],*const g_scene_contact_activity_six_palette3[],*const g_scene_contact_activity_six_palette4[];
extern const unsigned short g_scene_contact_activity_six_reset_palette[];
void display_show_background(unsigned int,unsigned int);
const unsigned short *display_load_background(unsigned int,const struct BackgroundResource*,unsigned short,unsigned short,unsigned int,unsigned int);
void frame_define_palette_slot(unsigned int,const void *const *);
void audio_game_select_activity_callback(unsigned int);
void scene_contact_activity_six_step_first(struct FrameObject*);
void scene_contact_activity_six_step_second(struct FrameObject*);
void scene_contact_activity_six_step_gauge(struct FrameObject*);
struct FrameObject *scene_contact_activity_six_create_primary(void);
struct FrameObject *scene_contact_activity_six_create_secondary(void);
struct FrameObject *scene_contact_activity_six_create_first(void);
struct FrameObject *scene_contact_activity_six_create_second(unsigned int);
struct FrameObject *scene_contact_activity_six_create_gauge(void);
void scene_contact_activity_six_check_pair(void);
struct SceneContactActivitySixAppearance {unsigned char group,unknown01,variant;};
extern struct SceneContactActivitySixAppearance g_scene_contact_activity_six_primary_appearance,g_scene_contact_activity_six_secondary_appearance;
extern struct FrameSpriteVariant **g_scene_contact_activity_six_part0_tables[];
extern struct FrameSpriteVariant ***g_scene_contact_activity_six_part1_tables[];
extern struct FrameSpriteVariant **g_scene_contact_activity_six_part2_tables[];
extern const void *const g_scene_contact_activity_six_character_palette[];
void frame_set_part_variants(struct FrameObject*,unsigned char,struct FrameSpriteVariant**,unsigned int);
/* The installed 728-byte primary update remains original. */
void scene_contact_activity_six_original_step_primary(struct FrameObject*);
void scene_contact_activity_six_step_secondary(struct FrameObject*);
void frame_disable_object_flags(struct FrameObject*,unsigned int);
unsigned char frame_object_has_flags(struct FrameObject*,unsigned int);
void scene_contact_activity_six_initialize(void),scene_contact_activity_six_step(void),scene_contact_activity_six_check_pair(void);
#endif
