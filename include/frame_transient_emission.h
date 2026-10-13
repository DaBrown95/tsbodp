#ifndef FRAME_TRANSIENT_EMISSION_H
#define FRAME_TRANSIENT_EMISSION_H

#include "frame_render_effect.h"
#include "frame_transient_effect.h"
#include "frame_random.h"

/* Signed integer halves of the observed two-word fixed-coordinate pairs. */
struct FrameTransientIntegerPoint {
    unsigned short fraction_x;
    short x;
    unsigned short fraction_y;
    short y;
};

unsigned char frame_read_attachment(struct FrameObject *, unsigned char,
                                    struct FramePoint *);
unsigned char frame_part_attachment_position(struct FrameObject *, unsigned char,
                                            unsigned char, struct FramePoint *);

extern unsigned char g_frame_transient_cardinal_directions[];
extern unsigned char g_actor_reverse_directions[];
extern unsigned char g_frame_transient_extended_directions[];
extern const int g_frame_transient_velocity_cardinal[];
extern const int g_frame_velocity_extended[];

#endif
