#ifndef DISPLAY_OBJECT_PALETTE_H
#define DISPLAY_OBJECT_PALETTE_H

struct FrameObject;
void frame_reset_object_palette_slots(void);
unsigned int frame_find_object_palette_slot(const void *const *);
unsigned char frame_count_free_object_palettes(void);
void frame_set_object_palette(struct FrameObject *, const void *);
void frame_set_subtype_object_palette(struct FrameObject *, const void *const *);
void frame_release_object_palette(struct FrameObject *);

#endif
