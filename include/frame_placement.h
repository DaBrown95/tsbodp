#ifndef FRAME_PLACEMENT_H
#define FRAME_PLACEMENT_H

struct FrameObject;
unsigned char frame_placement_begin(void *, struct FrameObject *, struct FrameObject *);
void frame_placement_cancel(void);
unsigned char frame_placement_rotate(unsigned int);
unsigned char frame_placement_move(unsigned int);
unsigned char frame_placement_confirm(void);
void frame_placement_reset_parameter(struct FrameObject *);
unsigned char frame_placement_validate(void);
void frame_placement_update_graphic(void);
void frame_placement_set_valid_palette(unsigned char);
struct FrameObject *frame_placement_create_preview(struct FrameObject *);

#endif
