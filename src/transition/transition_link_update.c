#include "event_record.h"
#include "link_state.h"
#define LINK_REG16(a) (*(volatile unsigned short *)(a))

int transition_link_update(void) {
 struct EventPayload payload;
 if (g_game_flags & 0x20) {
  if (link_transfer_finished() == 1) {
   unsigned int flags = g_game_flags;
   unsigned int mask = ~0x20u;
   g_link_flags &= ~4;
   g_game_flags = flags & mask;
   g_link_endpoint.identifier = -1;
   if (!(LINK_REG16(0x04000128) & 4))
    LINK_REG16(0x04000200) &= 0xFFBF;
   LINK_REG16(0x04000200) &= 0xFF7F;
   LINK_REG16(0x0400012A) = 0xFFFF;
   g_link_endpoint.active = 0;
   g_link_endpoint.slot = 0xFF;
   return 1;
  } else {
   *(unsigned int *)payload.storage.bytes = 0;
   if (g_link_recording & 1)
    transition_record_event(1, payload);
   else
    transition_record_event(3, payload);
  }
 }
 return 0;
}
