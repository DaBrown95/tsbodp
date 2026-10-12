#ifndef FRAME_ACTOR_INTERACTION_H
#define FRAME_ACTOR_INTERACTION_H
#include "resource_condition_entries.h"
struct FrameObject;
/* Partial option and local need views from selector22. Helper roles are provisional. */
struct FrameActorInteractionWork {
 unsigned char unknown_00[0x64]; struct FrameObject *effect;
 unsigned char mode,unknown_69[3]; unsigned int option_index;
};
struct FrameInteractionOption { unsigned char id,field1,field2,field3; };
struct FrameInteractionOptionList { unsigned int unknown00; struct FrameInteractionOption *entries; };
struct FrameInteractionWorld { unsigned char unknown00[0xf0]; struct FrameInteractionOptionList *options; };
struct FrameInteractionNeedWorld {
 unsigned char unknown00[0x40];
 struct FrameInteractionOptionList *options; unsigned char unknown44[0x348]; unsigned char selected_world;
};
extern struct FrameInteractionNeedWorld g_frame_actor_local_need_state;
struct FrameInteractionDefinition { unsigned char unknown00[12]; unsigned int special; unsigned char unknown10[8]; };
extern struct FrameInteractionDefinition g_frame_interaction_definitions[];
extern unsigned char g_frame_interaction_directions[];
unsigned char input_direction(unsigned char);
struct FrameObject *frame_spawn_need_effect(int,int,int,int,int);
void frame_enable_object_flags(struct FrameObject *,unsigned int);
void frame_interaction_begin_0802f4ec(void *,struct FrameObject *,struct FrameObject *);
void frame_interaction_cancel_0802f648(void);
unsigned char frame_interaction_confirm_0802f800(void);
void frame_interaction_step_0802f6b0(unsigned char);
void frame_interaction_select_0802f724(unsigned char);
void frame_interaction_idle_0802f8fc(void);
void frame_note_interaction_condition(unsigned int);
#endif
