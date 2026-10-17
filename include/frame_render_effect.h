#ifndef FRAME_RENDER_EFFECT_H
#define FRAME_RENDER_EFFECT_H
#include "frame_render.h"
#include "frame_pool.h"

/* Separate 84-byte pool records. Names follow observed accesses, not gameplay. */
struct FrameRenderEffect {
    struct FrameRenderEffect *next, *previous;
    unsigned int unknown08;
    const struct FrameSpriteResource *resource;
    struct FramePoint origin;
    union {
        struct FramePoint fixed;
        struct { unsigned short fraction_x; short x;
                 unsigned short fraction_y; short y; } pixel;
    } position;
    struct FramePoint velocity;
    union {
        struct FrameOam attributes;
        struct {
            unsigned char unknown28[5];
            unsigned char low2d : 2, layer : 2, high2d : 4;
            unsigned short padding2e;
        } priority;
    } sprite;
    unsigned int unknown30, unknown34;
    unsigned short *indices;
    short countdown;
    unsigned short unknown3e;
    unsigned int flags;
    unsigned short tile_first;
    short animation_ticks;
    signed char animation_delay, frame;
    unsigned char motion_mode, direction, phase, amplitude, phase_step;
    unsigned char unknown4f[5];
};
extern struct FrameRenderEffect *g_frame_render_effect_head;
extern struct FrameRenderEffect **g_frame_render_effect_lists[];
extern unsigned char g_frame_render_effect_counts[];
extern unsigned char g_frame_render_effect_free_pool[];
extern unsigned short g_frame_render_effect_count, g_frame_render_effect_maximum;
extern unsigned char g_frame_render_effect_pending;
extern unsigned char g_frame_render_direction_indices[];
extern const int g_frame_velocity_default[];

struct FrameRenderEffect *frame_allocate_render_effect(void);
void frame_destroy_render_effect(struct FrameRenderEffect *);
void frame_clear_render_effects(void);
int frame_step_uncollected_render_effects(void);
int frame_step_render_effect(struct FrameRenderEffect *);
void frame_step_render_effect_animation(struct FrameRenderEffect *);
void frame_step_render_effect_linear(struct FrameRenderEffect *);
void frame_step_render_effect_linear_alternate(struct FrameRenderEffect *);
int frame_draw_render_effect(struct FrameRenderEffect *);
unsigned char frame_render_effect_terrain(struct FrameRenderEffect *);

/* Canonical dependencies; the terrain argument is passed by value. */
int frame_fixed_multiply(int, int);
unsigned int frame_map_terrain_at(struct FramePoint);
#endif
