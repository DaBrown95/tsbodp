#include "frame_render.h"
extern unsigned char g_render_pending;
extern unsigned char *g_oam_previous;

void frame_prepare_oam_transfer(void) {
 unsigned int index;
 for (index = g_render_pending; index < 128; index++) {
  struct FrameOam *first=(struct FrameOam *)g_oam_previous;
  first+=index; first->display_mode=2;
  { struct FrameOam *second=(struct FrameOam *)g_oam_previous;
  second+=128; second+=index; second->display_mode=2; }
 }
 g_irq_context->transfer_ready = 1;
}
