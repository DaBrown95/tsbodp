/* Provisional names; the layout and handoff sequence follow original accesses. */
#include "irq.h"

struct AudioVBlankControl {
 unsigned char unknown[6];
 unsigned char flags : 8;
};
extern volatile unsigned int g_vblank_depth;
extern unsigned int g_oam_buffer_index;
extern unsigned char *g_oam_current, *g_oam_previous;
extern unsigned char g_oam_buffer_a[], g_oam_buffer_b[];
extern unsigned char g_render_pending, g_render_consumed;
extern volatile struct AudioVBlankControl g_audio_control;
extern void display_flush_palette_queue(void), background_animation_tick(void);
extern void display_flush_pending_block(void), display_commit_backgrounds(void);
extern void display_commit_windows(void), display_commit_palette_jobs(void);
extern void vblank_audio_step(void);
#define OAM_DMA (*(volatile struct DmaRegisters *)0x040000B0)
struct DmaRegisters { unsigned int source, destination, control; };

void irq_vblank(void) {
 unsigned int index;
 g_vblank_depth++;
 if (g_vblank_depth == 1) {
  g_oam_buffer_index ^= 1;
  index = g_oam_buffer_index;
  if (g_irq_context->transfer_ready) {
   if (g_oam_current == g_oam_buffer_a) {
    OAM_DMA.source = (unsigned int)(g_oam_buffer_b + (index << 10));
    OAM_DMA.destination = 0x07000000;
    OAM_DMA.control = 0x84000100;
    (void)OAM_DMA.control;
   } else {
    OAM_DMA.source = (unsigned int)(g_oam_buffer_a + (index << 10));
    OAM_DMA.destination = 0x07000000;
    OAM_DMA.control = 0x84000100;
    (void)OAM_DMA.control;
   }
   g_render_consumed = g_render_pending;
   g_render_pending = 0;
   display_flush_palette_queue();
   g_oam_current = g_oam_previous;
   if (g_oam_previous == g_oam_buffer_a) g_oam_previous = g_oam_buffer_b;
   else g_oam_previous = g_oam_buffer_a;
  } else {
   if (g_oam_current == g_oam_buffer_a) {
    OAM_DMA.source = (unsigned int)(g_oam_buffer_a + (index << 10));
    OAM_DMA.destination = 0x07000000;
    OAM_DMA.control = 0x84000100;
    (void)OAM_DMA.control;
   } else {
    OAM_DMA.source = (unsigned int)(g_oam_buffer_b + (index << 10));
    OAM_DMA.destination = 0x07000000;
    OAM_DMA.control = 0x84000100;
    (void)OAM_DMA.control;
   }
  }
  background_animation_tick();
  display_flush_pending_block();
  if (g_irq_context->vblank) g_irq_context->vblank();
  display_commit_backgrounds();
  display_commit_windows();
  display_commit_palette_jobs();
  g_irq_context->vblank_count++;
  g_irq_context->frame_60_count++;
  if (g_irq_context->frame_60_count > 59) {
   g_irq_context->previous_frame_work_count = g_irq_context->frame_work_count;
   g_irq_context->frame_work_count = 0;
   g_irq_context->frame_60_count = 0;
  }
  if (g_irq_context->transfer_ready) g_irq_context->transfer_ready = 0;
  REG16(0x04000202) = 1;
  g_irq_flags |= 1;
  if (!(g_audio_control.flags & 0x80)) {
   g_audio_control.flags &= 0xBF;
   vblank_audio_step();
  } else g_audio_control.flags |= 0x40;
 }
 g_vblank_depth--;
 REG16(0x04000208) = 0;
 REG16(0x03007FF8) |= 1;
 REG16(0x04000208) = 1;
}
