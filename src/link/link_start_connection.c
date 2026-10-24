#include "link_endpoint_setup.h"
#include "link_endpoint_active.h"

void link_start_connection(void)
{
    struct EventPayload payload;
    unsigned char *destination;
    g_game_flags |= 0x20;
    destination = &g_link_peer_count;
    *destination = link_read_endpoint_active();
    destination = &g_link_byte_03007340;
    *destination = event_get_link_slot();
    if (!*destination) {
        payload.storage.word = frame_random_bounded(65535);
        transition_record_event(2, payload);
    } else {
        payload.storage.word = 0;
        transition_record_event(1, payload);
    }
}
asm(".align 2, 0");
