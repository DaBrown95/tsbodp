#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H
#include "frame_scene_motion.h"
#include "heap.h"
#include "display_text_draw.h"
#include "display_text_raster.h"
/* Partial view used by text objects; gaps and the full allocation are unknown. */
struct DisplayTextObject {
    FrameU8 unknown_00[12];
    FrameU32 flags;
    FrameU8 unknown_10[192];
    struct FrameOam oam;
    FrameU16 width, height, columns;
    FrameU8 unknown_de[30];
    FrameU16 bytes, index;
    FrameU8 forced_visible;
};
struct DisplayTextDma {
    unsigned int source, destination, control;
};
#define DISPLAY_TEXT_DMA ((volatile struct DisplayTextDma *)0x040000d4)
extern void display_text_update(struct FrameObject *, const char **);
extern void display_scene_set_text_size(struct FrameObject *, const char *);
#endif
