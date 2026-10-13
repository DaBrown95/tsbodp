#ifndef FRAME_TRIGGER_OBJECTS_H
#define FRAME_TRIGGER_OBJECTS_H

#include "frame.h"
#include "input.h"
#include "resource_object_payload.h"
#include "transition_object.h"

/* Partial serialized payload; arguments have distinct roles in the two slots. */
struct FrameTriggerPayload {
    unsigned int id;
    short x, y;
    unsigned char width, height;
    unsigned short duration;
    unsigned char kind, argument0, argument1;
};

/* Local trigger view. The installed +C8 callback consumes two object arguments. */
struct FrameTriggerObject {
    unsigned char unknown00[8];
    unsigned short id, subtype;
    unsigned int flags;
    unsigned char owner_id, owner_slot, direction, unknown13[5];
    struct FramePoint position, next_position, velocity;
    unsigned char unknown30[0x4c - 0x30];
    unsigned char kind, state, variant_state, pending;
    unsigned char unknown50[8];
    int timer;
    unsigned char unknown5c[8];
    int duration;
    unsigned char unknown68[0x88 - 0x68];
    void (*on_step)(struct FrameObject *);
    unsigned char unknown8c[4];
    struct FrameObject *target;
    unsigned char unknown94[0xaf - 0x94];
    unsigned char bound_count;
    signed char left, right, top, bottom, bound_kind;
    unsigned char unknownb5[0xc8 - 0xb5];
    void (*on_interact)(struct FrameObject *, struct FrameObject *);
};

struct FrameCommandObject;
union ResourceGameState;
extern union ResourceGameState g_resource_game_state;
struct FrameObject *frame_allocate_scene_object(void);
void frame_set_position(struct FrameObject *, int, int);
void frame_request_animation(struct FrameCommandObject *, unsigned char);
void frame_set_variant_state(struct FrameObject *, unsigned char);
unsigned int audio_play_animation_cue(unsigned int);
void resource_activate_groups(unsigned char, unsigned char);
struct FrameObject *frame_create_actor_trigger(unsigned char, unsigned char);
struct FrameObject *frame_create_program_trigger(unsigned char, unsigned char);
void frame_trigger_actor_handoff(struct FrameObject *, unsigned int, struct FrameObject *);
void frame_actor_trigger_step(struct FrameObject *);
void frame_actor_trigger_interact(struct FrameObject *, struct FrameObject *);
void frame_program_trigger_step(struct FrameObject *);
void frame_program_trigger_interact(struct FrameObject *, struct FrameObject *);

#endif
