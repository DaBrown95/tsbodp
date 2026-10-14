#ifndef FRAME_CONTACT_ACTION_H
#define FRAME_CONTACT_ACTION_H
#include "display_time.h"

struct FrameObject;
struct CollisionObject;
struct FrameVariantResource;
struct FrameActorNeedState;

/* Factory slot 10 access views. Names describe observed contact, notice and
 * clock-gate operations; they are not recovered original identifiers. The
 * resource view starts at the aligned object base: its D1 byte is not a
 * separately cast aggregate. The mode at D1 bits 2..3 preserves bit 4. */
struct ContactActionPayload {unsigned int id;short x,y;unsigned char settings[4];};
struct ContactResourceView {
 unsigned char unknown00[0x64],settings[4],unknown68[0x88-0x68];
 void (*on_step)(struct FrameObject *);void (*on_remove)(struct FrameObject *);
 struct FrameObject *partner; unsigned char unknown94[0xaf-0x94],active;
 unsigned char unknownb0[4],enabled,unknownb5[0xc8-0xb5];
 void (*on_contact)(struct CollisionObject *,struct CollisionObject *);
 unsigned char unknowncc[5];
 unsigned char mode:2, contact_mode:2, unknown_d1_4:1, double_size:1, unknown_d1_6:2;
 unsigned char unknownd2[3],display_attrs;
};

struct ContactActionView {
 unsigned char unknown00[8]; unsigned short id;
 unsigned char unknown0a[0x4d-0x0a],state;
 unsigned char unknown4e[0x90-0x4e]; struct FrameObject *partner;
};

struct ContactTickView {
 unsigned char unknown00[0x4d],state,unknown4e[0x64-0x4e];
 unsigned char kind,parameter,first_hour,second_hour,unknown68[0x90-0x68];
 struct FrameObject *partner;
};
struct ContactWorldView {
 unsigned char unknown00[8];struct DisplayTimeRecord clock;
 unsigned char unknown10[0xb0-0x10];int needs[8];
 unsigned char unknownd0[0x735-0xd0],values[8],completed;
};
struct ContactCondition {unsigned char row,column,unknown02[2];};
struct ContactNotice {unsigned char unknown00,mode,kind,confirmed,active;};
extern struct ContactWorldView g_contact_action_world;
extern struct ContactCondition g_contact_action_conditions[];
extern unsigned short g_contact_action_messages[];
extern struct ContactNotice g_contact_action_notice;
union ContactClock {
 struct DisplayTimeRecord record;
 struct {unsigned int day:16,hour:8,minute:8;unsigned int tail;} fields;
};

struct FrameObject *frame_create_contact_resource(unsigned char, unsigned char);
void frame_begin_contact_action(struct CollisionObject *, struct CollisionObject *);
void frame_tick_contact_action(struct FrameObject *);
struct FrameObject *frame_allocate_scene_object(void);
void frame_acquire_palette_slot(struct FrameObject *, int);
void frame_set_position(struct FrameObject *, int, int);
void frame_update_actor_state(struct FrameObject *);
extern struct FrameVariantResource g_contact_action_animation;
unsigned char frame_actor_need_average(struct FrameActorNeedState *);
void frame_set_actor_direction(struct FrameObject *, unsigned char);
void scene_submit_default_request(unsigned int);
void resource_submit_scene(unsigned int, unsigned int, unsigned int);
extern unsigned char g_scene_mode_bytes[4];
extern const struct DisplayTimeRecord g_resource_selector_clock;
#endif
