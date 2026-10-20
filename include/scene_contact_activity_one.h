#ifndef SCENE_CONTACT_ACTIVITY_ONE_H
#define SCENE_CONTACT_ACTIVITY_ONE_H
#include "frame_actor_runtime.h"
#include "display.h"
#include "scene_request.h"
#include "audio_game_activity.h"
#include "input.h"
struct FrameCommandObject;
void transition_configure_view_move(struct FramePoint,int,unsigned short,unsigned char);
unsigned int transition_get_view_mode(unsigned char);
struct SceneContactState;
extern struct SceneContactState *g_scene_contact_state;
struct SceneContactActivityOneState {
 struct FrameObject *primary;unsigned char unknown04[8];
 short score;unsigned short attempts;
 unsigned char unknown10[3],option,phase,flags,unknown16[2];
 struct FrameObject *secondary;unsigned char counts[4];
};
struct SceneContactActivityOneObject {
 unsigned char unknown00[8];unsigned short id,subtype;unsigned int flags;
 unsigned char unknown10[0xc1];
 unsigned char mode:2,contact_mode:2,unknown_d1_4:1,double_size:1,unknown_d1_6:2;
 unsigned char unknown_d2[3];unsigned char tile_high:2,layer:2,palette:4;
};
struct SceneContactActivityOneAppearance {unsigned char group,unknown01,variant;};
extern struct SceneContactActivityOneAppearance g_scene_contact_activity_one_appearance;
extern const struct FramePoint g_scene_contact_activity_one_positions[];
extern struct FrameSpriteVariant **g_scene_contact_activity_one_part0_tables[];
extern struct FrameSpriteVariant ***g_scene_contact_activity_one_part1_tables[];
extern const unsigned int g_scene_contact_activity_one_background_control;
extern const struct BackgroundResource g_scene_contact_activity_one_background;
extern const void *const g_scene_contact_activity_one_palette1[],*const g_scene_contact_activity_one_palette2[];
extern struct FrameVariantResource g_scene_contact_activity_one_secondary_resources,g_scene_contact_activity_one_spawn_resources;
void display_show_background(unsigned int,unsigned int);
void display_fill_background(unsigned int,unsigned short);
const unsigned short *display_load_background(unsigned int,const struct BackgroundResource*,unsigned short,unsigned short,unsigned int,unsigned int);
void frame_define_palette_slot(unsigned int,const void *const *);
void frame_enable_object_flags(struct FrameObject*,unsigned int);
void frame_disable_object_flags(struct FrameObject*,unsigned int);
unsigned char frame_object_has_flags(struct FrameObject*,unsigned int);
void frame_set_variant_state(struct FrameObject*,unsigned char);
void frame_stop_motion(struct FrameObject*);
void frame_set_part_variants(struct FrameObject*,unsigned char,struct FrameSpriteVariant**,unsigned int);
void frame_set_animation_frame(struct FrameTickObject*,unsigned char);
void frame_update_map_view(unsigned char);
void transition_step_view(unsigned char);
void transition_run_first(unsigned short,unsigned int);
void transition_run_second(unsigned short,unsigned int);
void transition_configure_alpha(unsigned short,unsigned short);
void transition_set_alpha(unsigned short,unsigned short);
struct FrameObject *scene_contact_activity_one_create_primary(void),*scene_contact_activity_one_create_secondary(void),*scene_contact_activity_one_create_spawn(void);
void scene_contact_activity_one_step_primary(struct FrameObject*),scene_contact_activity_one_step_spawn(struct FrameObject*);
void scene_contact_activity_one_reward(void);
struct SceneContactActivityOneTimer {unsigned char unknown00[0x58];unsigned int countdown;};
unsigned int audio_play_animation_cue(unsigned int);
int save_world_scale_percent(int,int);
void scene_contact_add_activity_score(int);
void scene_contact_activity_one_accumulate_count(unsigned int,unsigned int);
extern struct SceneContactActivityOneState *g_scene_contact_activity_one_state;
void scene_contact_activity_one_initialize(void);
void scene_contact_activity_one_step(void);
#endif
