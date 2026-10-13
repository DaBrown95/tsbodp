#ifndef RESOURCE_COMMANDS_H
#define RESOURCE_COMMANDS_H

#include "resource_groups.h"
#include "audio_game.h"
#include "transition_object.h"

/* Offsets are relative to the serialized selector word, not a native pointer. */
#define COMMAND_BYTE(n) (command->parameters[(n)-4])
#define COMMAND_HALF(n) (*(const unsigned short *)(command->parameters+(n)-4))
#define COMMAND_SIGNED_HALF(n) (*(const short *)(command->parameters+(n)-4))
#define OBJECT_BYTE(object,n) (*((unsigned char *)(object)+(n)))
#define OBJECT_WORD(object,n) (*(unsigned int *)((unsigned char *)(object)+(n)))
#define OBJECT_POINTER(object,n) (*(struct FrameObject **)((unsigned char *)(object)+(n)))

extern void frame_set_variant_state(struct FrameObject *,unsigned char);
struct FrameCommandObject;
extern void frame_request_animation(struct FrameCommandObject *,unsigned char);
extern void frame_stop_motion(struct FrameObject *);
extern unsigned char frame_find_objects(unsigned char,unsigned char,struct FrameObject **,unsigned char);
extern int resource_scale_value(short);
extern void resource_prepare_object(struct FrameObject *);
extern void resource_submit_scene(unsigned int,unsigned int,unsigned int);
extern void resource_scene_event(unsigned int);
extern void resource_set_triple(unsigned int,unsigned int,unsigned int);
extern void resource_set_display_kind(unsigned int);
extern void resource_prepare_display(unsigned char);
extern unsigned char resource_select_actor(void *,unsigned char);
extern struct FrameObject *resource_create_transition(unsigned char);
extern void audio_game_pause(void),audio_game_resume(void);

extern void background_animation_load(int),background_animation_configure_alpha(void);

extern unsigned int g_game_flags;
extern unsigned char g_resource_selected;
extern unsigned char g_resource_view_records[];
extern unsigned char g_resource_display_kinds[];
extern void *g_resource_audio_handle,*g_resource_actor_context;
extern unsigned int g_resource_scene_arg;
extern unsigned char g_resource_view_modes[4];

/* Command-dependent fields form a partial view of the shared frame object. */
struct ResourceScriptState {
    unsigned char unknown00[77],state,variant;
    unsigned char pending : 8;
    unsigned char unknown50,mode,unknown52[6];
    int countdown;
    unsigned char unknown5c[8];
    union {
        unsigned int word;
        struct { unsigned char low,unknown65,parameter,signal; } bytes;
        struct FrameObject *target;
    } field64;
    union {
        unsigned int word;
        struct FrameObject *target;
        struct { unsigned short low,x; } positions;
    } field68;
    union {
        unsigned int word;
        struct { unsigned short y; unsigned char first,second; } positions;
    } field6c;
    unsigned char group_a,group_b,group_c,unknown73[6],argument_a,argument_b;
};
#define SCRIPT(o) ((struct ResourceScriptState *)(o))

#include "resource_view_effects.h"

#include "display_time.h"
extern struct DisplayTimeRecord g_resource_branch_default;
extern unsigned char g_resource_branch_context[];

/* Repeated 24-byte cells have a 144-byte row stride; the outer extent is unknown. */
struct ResourceViewCell {
    unsigned char first,second,unknown02[2];
    unsigned int values[5];
};
struct ResourceConditionalState {
    unsigned char unknown00[0x444];
    struct ResourceViewCell cells[1][6];
};
struct ResourceActorState {
    unsigned char unknown00[0x748];
    unsigned char selected_actor;
};
union ResourceGameState {
    struct ResourceConditionalState conditions;
    struct ResourceActorState actor;
};
extern union ResourceGameState g_resource_game_state;

#endif
