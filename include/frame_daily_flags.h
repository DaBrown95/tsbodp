#ifndef FRAME_DAILY_FLAGS_H
#define FRAME_DAILY_FLAGS_H

#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "display_time_daily.h"
#include "audio_game.h"

/* Selector-specific object prefix; this view does not establish allocation. */
struct FrameDailyFlagObject {
    unsigned char unknown00[10];
    unsigned short subtype;
    unsigned char unknown0c[0x4d - 0x0c];
    unsigned char state, variant_state, unknown4f[9];
    int timer;
    unsigned char unknown5c[8];
    struct FrameObject *owner;
    unsigned char index;
};
extern unsigned char g_scene_entry_data[];
int actor_entry_adjust_counter(void *, int, int);
void frame_enable_object_flags(struct FrameObject *, unsigned int);
void frame_disable_object_flags(struct FrameObject *, unsigned int);
void frame_step_daily_flag_object(struct FrameObject *);
unsigned int frame_test_daily_flag(unsigned int);

#endif
