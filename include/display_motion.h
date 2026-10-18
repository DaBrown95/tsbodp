#ifndef DISPLAY_MOTION_H
#define DISPLAY_MOTION_H
#include "display.h"
struct DisplayBackgroundSystem {
    struct DisplayControlState control;
    struct BackgroundState backgrounds[4];
};
extern struct DisplayBackgroundSystem g_display_background_system;
struct DisplayBackgroundWave {
    unsigned short phase_x, phase_y;
    short phase_step_x, phase_step_y, amplitude_x, amplitude_y;
};
extern void display_set_background_position(unsigned int index, int x, int y);
extern void display_set_background_scroll_target(unsigned int index, int x, int y,
    unsigned int duration);
extern void display_set_background_position_x(unsigned int index, int x);
extern void display_set_background_position_y(unsigned int index, int y);
extern void display_offset_background_position(unsigned int index, int x, int y);
extern void display_set_background_rotation(unsigned int index, unsigned short angle, unsigned short step);
extern void display_set_background_angle(unsigned int index, unsigned short angle);
extern void display_set_background_angle_step(unsigned int index, unsigned short step);
extern void display_set_background_center(unsigned int index, short x, short y);
extern void display_set_background_scale_limits(unsigned int index, short minimum, short maximum);
extern void display_set_background_scale_step(unsigned int index, unsigned short step);
extern void display_set_background_scale(unsigned int index, short scale);
extern void display_set_background_velocity(unsigned int index, int x, int y);
extern void display_set_background_velocity_x(unsigned int index, int x);
extern void display_set_background_velocity_y(unsigned int index, int y);
extern void display_reset_background_waves(unsigned int index);
extern void display_reset_background_wave_x(unsigned int index);
extern void display_reset_background_wave_y(unsigned int index);
extern void display_set_background_wave(unsigned int index, const struct DisplayBackgroundWave *wave);
extern void display_set_background_wave_x(unsigned int index, unsigned int phase, short step, short amplitude);
extern void display_set_background_wave_y(unsigned int index, unsigned int phase, short step, short amplitude);
extern void display_set_background_wave_phase(unsigned int index, unsigned int x, unsigned int y);
extern void display_set_background_wave_step(unsigned int index, short x, short y);
extern void display_set_background_wave_amplitude(unsigned int index, short x, short y);
#endif
