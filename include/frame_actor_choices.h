#ifndef FRAME_ACTOR_CHOICES_H
#define FRAME_ACTOR_CHOICES_H
#include "frame_actor_attachment.h"
#include "frame_actor_actions.h"
#include "frame_actor_scene.h"
#include "audio_game.h"
/* Category and penalty tables are inferred from selector31/32/33. */
struct FrameActorChoiceGame { unsigned char unknown00[0x440]; unsigned int stage; };
extern unsigned char g_actor_choice_categories[];
extern int g_actor_choice_penalties[][6];
struct FramePendingAction {
 struct FramePendingAction *next;
 unsigned char unknown04[0x50];
 struct FrameObject *target;
 unsigned char unknown58[4], action, unknown5d[19];
 unsigned short timer;
 unsigned char category;
};
extern struct FramePendingAction *g_frame_pending_action_head;
unsigned char frame_find_pending_action(unsigned int, struct FrameObject **, unsigned int *);
unsigned char frame_clear_pending_actions(unsigned int);
void frame_actor_show_action_failure(struct FrameObject *);
unsigned char frame_actor_route_to_target(struct FrameObject *, struct FrameObject *, unsigned char);
unsigned char frame_find_target_cell(void *, struct FrameObject *, struct FrameObject *, int *, unsigned char);
unsigned char frame_grid_cell_to_point(void *, const int *, struct FramePoint *);
#endif
