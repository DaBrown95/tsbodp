#ifndef SCENE_CONTACT_ACTIVITY_SEVEN_H
#define SCENE_CONTACT_ACTIVITY_SEVEN_H
#include "frame_actor_group.h"
#include "input.h"
#include "audio_game.h"
#include "display_text_fields.h"
#include "display_text_raster.h"
struct SceneContactState;
extern struct SceneContactState *g_scene_contact_state;
struct SceneContactActivitySevenState {
 struct FrameObject *primary;unsigned char unknown04[8];
 short score;unsigned short round;
 unsigned char unknown10[3],option,unknown14,flags,unknown16[2];
 struct FrameObject *status;unsigned int sample;
 unsigned char presses,failures;
};
struct SceneContactActivitySevenFlags {
 unsigned char unknown00[0xd1];
 unsigned char mode:2,contact_mode:2,unknown_d1_4:1,double_size:1,unknown_d1_6:2;
 unsigned char unknown_d2[3];unsigned char tile_high:2,layer:2,palette:4;
};
struct SceneContactActivitySevenTimedObject {unsigned char unknown00[0x58];int timer;};
struct SceneContactActivitySevenAppearance {unsigned char group,unknown01,variant;};
struct SceneContactActivitySevenGame {unsigned char unknown00[0x20],gender;};
struct SceneContactActivitySevenRound {unsigned char label,first,second,third,reward,unknown05[3];};
struct SceneContactActivitySevenOption {struct SceneContactActivitySevenRound rounds[4];unsigned char timer,unknown21[3];};
extern const struct SceneContactActivitySevenOption g_scene_contact_activity_seven_options[];
extern struct SceneContactActivitySevenAppearance g_scene_contact_activity_seven_appearance;
extern struct FrameSpriteVariant **g_scene_contact_activity_seven_part0[];
extern struct FrameSpriteVariant ***g_scene_contact_activity_seven_part2[];
extern struct FrameSpriteVariant ***g_scene_contact_activity_seven_part1[];
extern const void *const g_scene_contact_activity_seven_palette1[],*const g_scene_contact_activity_seven_palette2[],*const g_scene_contact_activity_seven_palette3[];
extern const unsigned int g_scene_contact_activity_four_background1,g_scene_contact_activity_four_background2,g_scene_contact_initial_background_control1;
extern const struct BackgroundResource g_scene_contact_activity_seven_background1,g_scene_contact_activity_seven_background2,g_scene_contact_activity_seven_background3;
extern struct FrameVariantResource g_scene_contact_activity_seven_status_animation,g_scene_contact_activity_seven_effect_first_animation,g_scene_contact_activity_seven_effect_second_animation;
void frame_define_palette_slot(unsigned int,const void *const *);
void display_show_background(unsigned int,unsigned int);
const unsigned short *display_load_background(unsigned int,const struct BackgroundResource*,unsigned short,unsigned short,unsigned int,unsigned int);
void display_clear_background_rectangle(unsigned int,int,int,int,int);
void frame_enable_object_flags(struct FrameObject*,unsigned int);
void frame_disable_object_flags(struct FrameObject*,unsigned int);
unsigned char frame_object_has_flags(struct FrameObject*,unsigned int);
void frame_set_animation_frame(struct FrameTickObject*,unsigned char);
void scene_contact_add_activity_score(int);
struct FrameObject *scene_contact_activity_seven_create_primary(void),*scene_contact_activity_seven_create_status(void),*scene_contact_activity_seven_create_effect(unsigned char);
void scene_contact_activity_seven_initialize(void),scene_contact_activity_seven_step(void),scene_contact_activity_seven_draw_status(void);
void scene_contact_activity_seven_step_primary(struct FrameObject*),scene_contact_activity_seven_step_effect(struct FrameObject*);
void scene_contact_activity_seven_retreat(struct FrameObject*,unsigned int,unsigned int);
unsigned char scene_contact_activity_seven_advance(struct FrameObject*,unsigned char,unsigned int,unsigned int);
unsigned char scene_contact_activity_seven_finish_animation(struct FrameObject*,unsigned int,unsigned int);
#define STATE ((struct SceneContactActivitySevenState *)g_scene_contact_state)
#define FLAGS(o) ((struct SceneContactActivitySevenFlags *)(o))
#define TIMER(o) ((struct SceneContactActivitySevenTimedObject *)(o))->timer
#define GAME ((struct SceneContactActivitySevenGame *)&g_resource_game_state)
#endif
