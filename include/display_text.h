#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H
#include "frame_scene_motion.h"
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
extern void *display_text_allocate_metrics(unsigned int);
extern void *display_text_allocate_pixels(unsigned int);
extern void display_text_set_buffers(void *, void *, unsigned int);
extern void display_text_draw(unsigned int, unsigned int, unsigned int,
                              unsigned int, const char **, unsigned int,
                              unsigned int *);
extern void display_text_free_buffer(void *);
#endif
