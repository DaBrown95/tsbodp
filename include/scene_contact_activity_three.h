#ifndef SCENE_CONTACT_ACTIVITY_THREE_H
#define SCENE_CONTACT_ACTIVITY_THREE_H
/* Observed activity-three access prefixes; capacities and names are provisional. */
#include "display.h"
#include "frame_actor_runtime.h"
#include "audio_game.h"
#include "input.h"
struct FrameObject;struct SceneContactState;
extern struct SceneContactState *g_scene_contact_state;
struct SceneContactActivityThreeState {
 unsigned char unknown00[10];unsigned short sound_timer;short active_rows;unsigned short restore_sequence;
 unsigned char unknown10[3],option,unknown14,flags,unknown16[2];
 struct FrameObject *primary,*secondary,*cursor;union {struct FrameObject *object;unsigned int address;} observer;struct FrameObject *event;
 struct FramePoint row_origins[5];unsigned int sound_handle;unsigned char values[3],completed;
};
struct SceneContactActivityThreeControl {
 unsigned char unknown00[8];unsigned int refresh_count;
 union {unsigned int word;unsigned char bytes[4];} selection;
 unsigned int phase,timer;
};
struct SceneContactActivityThreeOption {unsigned char values[3],unknown03;};
struct SceneContactActivityThreeBackgroundEntry {const struct BackgroundResource *background;const void *palette;int scale;};
extern struct SceneContactActivityThreeControl g_scene_contact_activity_three_control;
extern const struct SceneContactActivityThreeOption g_scene_contact_activity_three_options[];
extern const struct SceneContactActivityThreeBackgroundEntry g_scene_contact_activity_three_background_entries[];
extern const unsigned int g_scene_contact_initial_background_control1,g_scene_contact_activity_four_background2,g_scene_contact_activity_four_background1;
extern const struct BackgroundResource g_scene_contact_activity_three_background3,g_scene_contact_activity_three_background2;
extern const struct PaletteRangeConfig g_scene_contact_activity_three_palette_ranges;
extern const void *const g_scene_contact_activity_three_palette15[],*const g_scene_contact_activity_three_palette14[];
void display_show_background(unsigned int,unsigned int);
const unsigned short *display_load_background(unsigned int,const struct BackgroundResource*,unsigned short,unsigned short,unsigned int,unsigned int);
struct FrameObject *scene_contact_activity_three_create_primary(void),*scene_contact_activity_three_create_secondary(void),*scene_contact_activity_three_create_observer(void),*scene_contact_activity_three_create_cursor(void);
void scene_contact_activity_three_clear_slots(void);
struct FrameObject *scene_contact_activity_three_create_row(unsigned int);
void scene_contact_activity_three_refresh_value(unsigned int,unsigned int);
struct SceneContactActivityThreeObject {
 unsigned char unknown00[8];unsigned short id,subtype;unsigned int flags;
 unsigned char unknown10[2],direction,unknown13;int speed;
 struct FramePoint position,next_position,velocity,acceleration,destination;
 unsigned char unknown40[12],amount,phase,outcome,palette_source,unknown50[8];unsigned int timer;unsigned char unknown5c[44];
 void (*on_step)(struct FrameObject*);unsigned char unknown8c[0x45];
 unsigned char mode:2,contact_mode:2,unknown_d1_4:1,double_size:1,unknown_d1_6:2;
 unsigned char unknown_d2;unsigned char unknown_d3_low:4,secondary:1,unknown_d3_high:3;unsigned char unknown_d4;
 unsigned char tile_high:2,layer:2,palette:4;
 unsigned char unknown_d6[2],delay,frame_delay,previous_frame,frame;struct FrameSpriteResource *resource;
};
struct FrameObject *frame_allocate_scene_object(void);
unsigned int input_step_vertical_pressed(unsigned int*,unsigned int,unsigned int,unsigned char,unsigned char);
unsigned int scene_contact_activity_three_get_value(unsigned int);
struct FrameObject *scene_contact_activity_three_create_event(void);
extern struct FrameVariantResource g_scene_contact_activity_three_primary_animation,g_scene_contact_activity_three_secondary_animation;
extern unsigned char g_scene_contact_activity_three_primary_commands[],g_scene_contact_activity_three_secondary_commands[];
#include "display_text_draw.h"
#include "display_text_fields.h"
#include "display_text_raster.h"
struct SceneContactActivityThreeSlots {struct FrameObject *objects[16];unsigned int count;struct FramePoint delta,origin,endpoint,step;unsigned char horizontal,unknown65[3];};
extern struct SceneContactActivityThreeSlots g_scene_contact_activity_three_slots;
extern struct FrameVariantResource g_scene_contact_activity_three_observer_animation,g_scene_contact_activity_three_cursor_animation,g_scene_contact_activity_three_event_animation;
void scene_contact_activity_three_step_event(struct FrameObject*),scene_contact_activity_three_step_row(struct FrameObject*);
void scene_contact_activity_three_original_prepare_row(struct FrameObject*),scene_contact_activity_three_reset_row(struct FrameObject*);
void display_clear_background_rectangle(unsigned int,int,int,int,int);
void *heap_clear(void*,int,unsigned int);
#include "view_math.h"
extern struct FramePoint g_view_direction_vectors[];
void scene_contact_activity_three_advance_vector(struct FrameObject*,int,unsigned int);
unsigned int scene_contact_activity_three_direction_to_point(int,int,int,int);
void scene_contact_activity_three_remove_slots(void),scene_contact_activity_three_original_draw_event(struct FrameObject*);
void frame_remove_object(struct FrameObject*);
struct SceneContactActivityThreeRowDefinition {
 struct FrameVariantResource animation;unsigned char unknown10[20];const struct BackgroundResource *background;unsigned char unknown28[4];int speed;
 unsigned char minimum,maximum,threshold,escape_threshold;unsigned short sequence,sound_timer;
};
struct SceneContactActivityThreePhaseDefinition {int scale;unsigned char threshold,unknown05,probability,frame_delay;};
extern struct SceneContactActivityThreeRowDefinition g_scene_contact_activity_three_row_definitions[];
extern const struct SceneContactActivityThreePhaseDefinition g_scene_contact_activity_three_phase_definitions[];
extern const unsigned char g_scene_contact_activity_three_direction_frames[];
extern struct FrameVariantResource g_scene_contact_activity_three_row_normal_animations[],g_scene_contact_activity_three_row_special_animations[];
struct FrameAffineObject;struct FrameTickObject;
void frame_set_affine_scale(struct FrameAffineObject*,int,int,int);
void frame_set_animation_frame(struct FrameTickObject*,unsigned char);
int frame_random_range(int,int);
void scene_contact_activity_three_queue_row_palette(struct FrameObject*);
void scene_contact_activity_three_scale_row(struct FrameObject*,int,int);
void scene_contact_activity_three_update_linked_row(struct FrameObject*);
void scene_contact_activity_three_decrement_value(unsigned int);
void scene_contact_activity_three_step(void);
void scene_contact_activity_three_step_event(struct FrameObject*),scene_contact_activity_three_step_row(struct FrameObject*);
void scene_contact_activity_three_get_observer_point(struct FramePoint*);
void scene_contact_activity_three_reset_row(struct FrameObject*);
void scene_contact_activity_three_remove_slots(void);
void display_fill_background(unsigned int,unsigned short);
void scene_contact_activity_three_initialize(void);
void scene_contact_add_activity_score(int);
extern struct FrameVariantResource g_scene_contact_activity_three_line_animation;
void scene_contact_activity_three_ensure_line_slot(unsigned int,int,int);
unsigned int scene_contact_activity_three_raster_line_slot(unsigned int);
void scene_contact_activity_three_plot_line_pixel(unsigned short*,int,int);
void scene_contact_activity_three_update_line_slots(void);
#endif
