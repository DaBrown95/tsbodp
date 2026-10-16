#include "transition.h"
#include "irq.h"
#include "event_record.h"
extern unsigned int g_transition_frame_period;
extern int transition_link_update(void);
#define REG_BLDCNT (*(volatile unsigned short *)0x04000050)
#define REG_BLDY (*(volatile unsigned short *)0x04000054)

void transition_fade_black_in_record(unsigned short targets) {
 int level;
 struct EventPayload payload;
 REG_BLDCNT = targets | 0xC0;
 g_game_flags |= 0x2000;
 for (level=16; level>=0; level--) {
  REG_BLDY = level;
  transition_link_update();
  *(unsigned int *)payload.storage.bytes = 0;
  transition_record_event(1, payload);
  transition_frame_update_08001168();
  transition_stage_0802d054();
  do {
   int elapsed;
   irq_wait_vblank();
   elapsed = g_irq_context->vblank_count - g_irq_context->previous_vblank_count;
   if (elapsed < 0) elapsed = -elapsed;
   if ((unsigned int)elapsed >= g_transition_frame_period) break;
  } while (1);
  g_irq_context->previous_vblank_count = g_irq_context->vblank_count;
 }
 g_game_flags &= ~0x2000;
}
