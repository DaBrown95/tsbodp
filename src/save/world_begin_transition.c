#include "save_world_initialization.h"

void save_world_begin_transition(unsigned int index)
{
    struct SaveWorldTransitionRow *table = g_save_world_transition_rows;
    struct SaveWorldTransitionRow *row = &table[index];
    unsigned int zero = 0;
    unsigned int duration = 20;
    row->ticks = duration;
    display_configure_window(1, 62, 63);
    display_set_window_rectangle(1, 40 << 16, 120 << 16, 240 << 16, 120 << 16);
    display_begin_window_axis_move(1, 1, 240 << 16, 160 << 16, duration);
    row->ready = zero;
    audio_play_animation_cue(12);
}
asm(".align 2, 0");
