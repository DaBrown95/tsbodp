#ifndef FRAME_MOVEMENT_REDIRECT_H
#define FRAME_MOVEMENT_REDIRECT_H
#include "frame_terrain_classifier.h"

/* Partial byte view of the common object's direction at +18. */
struct FrameMovementRedirectDirection {
    unsigned char unknown_00[18], direction;
};
union FrameMovementNibbleSnapshot {
    unsigned int word;
    struct { unsigned char low : 4, high : 4; } byte;
};
extern const union FrameTerrainLine g_frame_movement_direction_lines[];
extern unsigned int g_frame_movement_filter[2];

unsigned char frame_movement_direction_blocked(struct FrameObject *, struct FramePoint);
unsigned char frame_movement_offset_blocked(struct FrameObject *, struct FramePoint);
void frame_redirect_movement(struct FrameObject *, unsigned int);
#endif
