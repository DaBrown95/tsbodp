#ifndef FRAME_RENDER_VARIANT_RESOURCE_H
#define FRAME_RENDER_VARIANT_RESOURCE_H

struct FrameObject;
struct FrameVariantResource;

/* The factory reads bytes 0..8 through this word-aligned access view. */
struct FrameRenderVariantPayload {
    unsigned int selector_word;
    short x, y;
    unsigned char subtype;
};

/* Whole-object prefix: the observed bitfield stores are at +0xd1 and +0xd5. */
struct FrameRenderVariantFlags {
    unsigned char unknown00[0xd1];
    unsigned char mode : 2, contact_mode : 2, unknown_d1_4 : 1;
    unsigned char double_size : 1, unknown_d1_6 : 2;
    unsigned char unknown_d2_d4[3];
    unsigned char tile_high : 2, layer : 2, palette : 4;
};

/* Observed pointer roots; these declarations do not establish array capacity. */
extern struct FrameVariantResource *const g_frame_render_variant_animations[];
extern const void *const g_frame_render_variant_palette[];
struct FrameObject *frame_create_render_variant_resource(unsigned char, unsigned char);

#endif
