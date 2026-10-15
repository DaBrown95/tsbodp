#ifndef TRANSITION_MOSAIC_H
#define TRANSITION_MOSAIC_H

#include "frame.h"
#include "display_palette_lifecycle.h"

FrameU8 frame_request_refresh(void);
void display_step_backgrounds(void);
void frame_prepare_oam_transfer(void);
void irq_wait_vblank(void);
void transition_mosaic_darkening_refresh(unsigned short);
void transition_mosaic_lightening_refresh(unsigned short);

#endif
