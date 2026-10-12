#ifndef VIEW_EFFECTS_H
#define VIEW_EFFECTS_H

#include "resource_commands.h"
#include "view_math.h"

/* Forty-eight-byte view motion records; unnamed points remain provisional. */
struct ResourceViewMotion {
    struct FrameObject *object;
    struct FramePoint position,unknown0c,unknown14,target;
    int speed;
    unsigned short mode,unknown2a,delay;
    unsigned char interpolate,unknown2f;
};
extern struct ResourceViewMotion g_resource_view_motion[];
extern struct FramePoint g_view_direction_vectors[];


void transition_reset_view(unsigned char);
unsigned char transition_approach_view(struct FramePoint,int,unsigned char);
void transition_configure_view_move(struct FramePoint,int,unsigned short,unsigned char);

unsigned short transition_get_view_mode(unsigned char);
void transition_set_view_origin(struct FramePoint, unsigned char);
void transition_get_view_position(struct FramePoint *, unsigned char);
#endif
