#ifndef SCENE_CONTACT_ACTIVITY_FIVE_H
#define SCENE_CONTACT_ACTIVITY_FIVE_H
/* Observed access views for definition row five; names and capacities are provisional. */
#include "display.h"
#include "frame.h"
#include "scene_request.h"
#include "input.h"
#include "frame_random.h"
#include "audio_game.h"
#include "scene_contact_activity.h"
struct SceneContactState;
extern struct SceneContactState *g_scene_contact_state;
struct SceneContactActivityFiveObject {
 struct SceneContactActivityFiveObject *next,*previous;
 unsigned short id,subtype;unsigned int flags;
 unsigned char unknown10[8];
 struct FramePoint position,next_position,velocity,acceleration,destination;
 unsigned char unknown40[13],phase,cell,unknown4f[9];unsigned int timer;
 unsigned char unknown5c[44];void (*on_step)(struct FrameObject *);
 unsigned char unknown8c[0x45];
 unsigned char mode:2,contact_mode:2,unknown_d1_4:1,double_size:1,unknown_d1_6:2;
 unsigned char unknown_d2[3];unsigned char tile_high:2,layer:2,palette:4;
 unsigned char unknown_d6[2],frame;
};
struct SceneContactActivityFiveState {
 struct FrameObject *root;
 unsigned char unknown04[8];
 short score;unsigned short combo_count;
 unsigned char unknown10[3], option, unknown14, flags;
 unsigned char unknown16[2];
 struct SceneContactActivityFiveObject *objects[64];
 struct {int timer;unsigned int unknown04;} timed[5];
 union {unsigned char rows[8][8],flat[64];} cells;
 signed char column_heights[8];
 unsigned char pending_column_shifts[8];
 int selected_column,selected_row,column_count;unsigned int selected_count;
 signed char settle_row;
};
struct SceneContactActivityFiveRow {unsigned char subtype_count,combo_reward,reward,chance;};
extern const struct SceneContactActivityFiveRow g_scene_contact_activity_five_rows[];
extern const unsigned int g_scene_contact_activity_four_background1;
extern const struct BackgroundResource g_scene_contact_activity_five_background1,g_scene_contact_activity_five_background3;
void scene_contact_activity_five_initialize(void);
void scene_contact_activity_five_step(void);
struct FrameObject *scene_contact_activity_five_create_root(void);
void scene_contact_activity_five_populate(void);
void scene_contact_activity_five_reset_timers(void);
void scene_contact_activity_five_apply_selection(int,int,unsigned int,unsigned int);
void scene_contact_activity_five_refresh_timer(int);
void scene_contact_activity_five_set_timer(int,unsigned int);
void scene_contact_activity_five_rebuild_cells(void);
void scene_contact_activity_five_compact_columns(void);
struct FrameVariantResource;struct FrameTickObject;struct FrameSpriteResource;
extern unsigned char g_scene_contact_activity_five_cell_animations[],g_scene_contact_activity_five_cell_program[];
void frame_set_animation_program(struct FrameObject *,struct FrameSpriteResource *,unsigned char *,unsigned char);
extern struct FrameVariantResource g_scene_contact_activity_five_followup_animation;
extern struct FrameVariantResource g_scene_contact_activity_five_root_animation;
void scene_contact_activity_five_step_root(struct FrameObject *);
void scene_contact_activity_five_set_cell_frame(struct FrameObject *);
void scene_contact_activity_five_assign_timer(int,int);
void scene_contact_activity_five_step_followup(struct FrameObject *);
struct FrameObject *frame_allocate_object(int);
void frame_set_position(struct FrameObject *,int,int);
void frame_set_animation_record(struct FrameObject *,struct FrameVariantResource *);
void frame_set_animation_frame(struct FrameTickObject *,unsigned char);
InputU32 input_step_vertical_pressed(InputU32 *,InputU32,InputU32,InputU8,InputU8);
InputU32 input_step_horizontal_pressed(InputU32 *,InputU32,InputU32,InputU8,InputU8);
void *heap_clear(void *,int,unsigned int);
int display_bios_remainder(int,int);
void scene_contact_activity_five_reset(void);
void scene_contact_activity_five_refresh(void);
void scene_contact_activity_five_update_selection(void);
void scene_contact_activity_five_reset_selection(void);
void scene_contact_activity_five_set_selection(int,int);
void scene_contact_activity_five_remove_marked_cells(void);
unsigned char scene_contact_activity_five_selection_finished(void);
unsigned char scene_contact_activity_five_advance(void);
unsigned char scene_contact_activity_five_has_adjacent_pair(void);
void scene_contact_activity_five_clamp_selection(void);
struct FrameObject *scene_contact_activity_five_create_followup(void);
void scene_contact_activity_five_begin_end(void);
void scene_contact_add_activity_score(int);
void display_show_background(unsigned int,unsigned int);
const unsigned short *display_load_background(unsigned int,const struct BackgroundResource *,unsigned short,unsigned short,unsigned int,unsigned int);
struct FrameObject *scene_contact_activity_five_create_cell(unsigned int,int,int);
void scene_contact_activity_five_step_cell(struct FrameObject *);
void scene_contact_activity_five_set_cell_timer(int,int,unsigned char);
extern const void *const g_scene_contact_activity_five_cell_palettes[];
void frame_set_subtype_object_palette(struct FrameObject *,const void *const *);
extern struct FrameVariantResource g_scene_contact_activity_five_followup_finish_animation;
void scene_contact_activity_five_replace_cell(int,int);
#endif
