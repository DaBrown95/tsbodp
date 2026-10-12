#ifndef FRAME_ACTOR_IDLE_H
#define FRAME_ACTOR_IDLE_H
struct FrameObject;
struct FramePoint;
/* Partial game-state and object views; signed tick counters retain observed loads. */
struct FrameActorIdleGlobals {
 unsigned char unknown00[0x741]; signed char counter_reduction_tick,counter_addition_tick;
 unsigned char unknown743[6],variant,unknown74a[2]; int timer;
};
struct FrameActorIdleWork {
 unsigned char unknown00[0x58]; int timer;
 unsigned short movement_units,countdown;
};
extern unsigned int g_game_flags;
extern unsigned char g_actor_need_step_mode;
void frame_reduce_actor_scene_counter(void);
void frame_add_actor_scene_counter_rate(void);
void frame_actor_input_velocity(struct FrameObject *,struct FramePoint *);
unsigned char frame_world_in_idle_exclusion_set(unsigned int);
void frame_set_actor_need_step_mode(unsigned int);
void frame_cycle_idle_actor_palette(void);
struct FrameActorPaletteSelection {unsigned char unknown00[0x42d],palette;};
unsigned int frame_get_actor_palette_slot(struct FrameObject *);
void frame_acquire_palette_slot(struct FrameObject *,int);
extern unsigned short g_actor_scene_counter_rates[];
void frame_actor_state_16(struct FrameObject *);
#endif
