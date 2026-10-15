#ifndef SCENE_RECORD_SELECTION_HANDOFFS_H
#define SCENE_RECORD_SELECTION_HANDOFFS_H
#include "scene_record_selection.h"
#include "frame_actor_palette_scene_points.h"
#include "display_motion.h"
#include "heap.h"
void frame_scene_object_tick(struct FrameObject *);
void transition_object_set_state(void *, unsigned char);
void frame_set_position(struct FrameObject *, int, int);
void frame_begin_position_move(struct FrameObject *, int, int, unsigned short);
unsigned char frame_step_position_move(struct FrameObject *);
void frame_set_variant_state(struct FrameObject *, unsigned char);
void display_set_background_scroll_target(unsigned int, int, int, unsigned int);
void transition_run_second(unsigned short, unsigned int);
void audio_game_clear_indexed_channels_alternate(void);
void display_release_object_list(struct FrameObjectList *);
void display_reset(void);
void display_scene_clear_object_slots(void);
void scene_record_selection_set_phase(unsigned char, unsigned int);
void scene_record_selection_set_slot_phase(unsigned char, unsigned int);
void scene_record_selection_shutdown(void);
#endif
