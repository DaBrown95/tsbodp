#ifndef FRAME_ACTOR_ACTIONS_H
#define FRAME_ACTOR_ACTIONS_H
struct FrameObject;
struct SceneModeFlags;
/* Partial views of timed actor action descriptors and notification state. */
struct FrameActorActionWork {
 unsigned char unknown00[0x58]; int timer; unsigned char unknown5c[8];
 unsigned short action;
 /* Catalog confirmation writes the halfword; state 19 consumes its low byte. */
 union __attribute__((packed,aligned(2))) {
  unsigned char bytes[2];
  unsigned short word;
 } variation;
 unsigned int cue_handle;
};
typedef char frame_actor_action_work_layout[(sizeof(struct FrameActorActionWork)==108&&__alignof__(struct FrameActorActionWork)==4&&(unsigned int)&((struct FrameActorActionWork*)0)->action==0x64&&(unsigned int)&((struct FrameActorActionWork*)0)->variation==0x66&&sizeof(((struct FrameActorActionWork*)0)->variation)==2&&(unsigned int)&((struct FrameActorActionWork*)0)->cue_handle==0x68)?1:-1];
struct FrameActorActionDefinition {
 unsigned int id; unsigned short duration; unsigned char animation,variant;
 unsigned char need,amount,unknown0a[2];
};
extern struct FrameActorActionDefinition g_frame_actor_action_definitions[];
signed char frame_find_actor_action(unsigned int);
void frame_note_actor_action(unsigned short);
int frame_add_game_value(int);
void frame_advance_parameter_level(void *,unsigned int);
#include "condition_actor.h"
struct FrameActorValueWorld { unsigned int unknown00; int value; };
struct SceneModeFlags;
extern struct SceneModeFlags g_scene_mode_flags;

struct FrameActorParameterNotification { unsigned char unknown00,x,y,unknown03,active; };
extern unsigned char g_frame_parameter_refresh_context[];
int display_text_measure_height(const char *);

#endif
