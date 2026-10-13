#ifndef FRAME_ACTOR_GROUP_H
#define FRAME_ACTOR_GROUP_H

#include "frame_actor_runtime.h"
#include "display.h"
#include "heap.h"

union ResourceGameState;
extern union ResourceGameState g_resource_game_state;

/* Access views for the signed animation byte and selected fallback palette. */
struct __attribute__((packed)) FrameActorGroupAnimationView {
    unsigned char unknown_00[0x103];
    signed int animation : 8;
};
struct FrameActorGroupGameView {
    unsigned char unknown_00[0x42d], palette;
};
/* First and last halfwords surround five independently selected byte ranges. */
struct FrameActorGroupPaletteAnchors {
    unsigned short first;
    unsigned char middle[28];
    unsigned short last;
};

extern struct FrameSpriteVariant **g_actor_group_part0_tables[];
extern struct FrameSpriteVariant ***g_actor_group_part1_tables[];
extern struct FrameSpriteVariant **g_actor_group_part2_tables[];
extern const unsigned char g_actor_group_part2_palette[];
extern const unsigned short g_actor_group_palette_rows[];

void frame_set_part_variants(struct FrameObject *, unsigned char,
                             struct FrameSpriteVariant **, unsigned int);
void frame_clear_part_variants(struct FrameObject *, unsigned char);

#endif
