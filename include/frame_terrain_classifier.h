#ifndef FRAME_TERRAIN_CLASSIFIER_H
#define FRAME_TERRAIN_CLASSIFIER_H
#include "frame.h"
#include "frame_layer.h"

/* Four-byte ROM line records expose four unsigned low-halfword nibbles. */
union FrameTerrainLine {
    unsigned int word;
    unsigned char bytes[4];
    struct {
        unsigned char x0 : 4, y0 : 4, x1 : 4, y1 : 4;
        unsigned short unknown;
    } nibble;
};
extern const union FrameTerrainLine g_frame_movement_contact_lines[];
unsigned int frame_map_terrain_at(struct FramePoint);
#endif
