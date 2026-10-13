#include "link_event_receive.h"

void link_apply_received_events(void)
{
    unsigned int i;
    g_link_flags &= ~0x80u;
    for (i = 0; i < g_link_peer_count; i++) {
        struct EventRecord *record = &g_link_received_events[i];
        const unsigned short *input = (const void *)record;
        event_get_link_slot();
        if (record->sequence != g_link_received_sequence[i] && record->kind) {
            g_link_received_sequence[i] = record->sequence;
            g_link_received_input[i] = 0;
            switch (record->kind) {
            case 3:
                g_link_received_input[i] = input[2];
                if (event_get_link_slot() == i)
                    g_link_flags |= 0x80;
                break;
            case 2:
                frame_set_random_seed(record->payload.halfwords[0]);
                break;
            case 4:
                if (i == 0) g_link_flags |= 0x100000;
                else if (i == 1) g_link_flags |= 0x200000;
                else if (i == 2) g_link_flags |= 0x400000;
                else if (i == 3) g_link_flags |= 0x800000;
                break;
            case 5:
                if (g_link_received_join.identifier == -1) {
                    if (i == 0) {
                        g_link_flags |= 0x100000;
                        g_link_received_join.identifier = i;
                    } else if (i == 1) {
                        g_link_flags |= 0x200000;
                        g_link_received_join.identifier = i;
                    } else if (i == 2) {
                        g_link_flags |= 0x400000;
                        g_link_received_join.identifier = i;
                    } else if (i == 3) {
                        g_link_flags |= 0x800000;
                        g_link_received_join.identifier = i;
                    }
                    g_link_received_join.metadata[0] = g_link_peer_count;
                    g_link_received_join.metadata[1] = record->payload.bytes[1];
                    g_link_received_join.metadata[2] = record->payload.bytes[2];
                    g_link_received_join.metadata[3] = record->payload.bytes[3];
                    g_scene_request.unknown_10 = 4;
                }
                break;
            case 7:
                g_link_received_join.values[i] = record->payload.word;
                break;
            case 8:
                display_text_copy_bytes(&g_link_received_pairs[i].first,
                                        &record->payload, 8);
                break;
            case 9:
                display_text_copy_bytes(&g_link_received_pairs[i].second,
                                        &record->payload, 8);
                break;
            case 11:
                g_link_flags |= 0x80000;
                g_game_flags &= ~0x20u;
                g_link_flags |= 0x8000;
                resource_submit_scene(1, 2, g_scene_id);
                break;
            case 10: {
                unsigned int address = i * sizeof(struct EventPayload);
                address += (unsigned int)g_link_received_vectors;
                *(struct EventPayload *)address =
                    *(struct EventPayload *)&record->payload;
                break;
            }
            case 12: link_apply_received_actor_entry(); break;
            case 13: link_show_received_entry_notice(); break;
            case 0: case 1: case 6: break;
            }
        }
        {
            unsigned int zero = 0;
            display_cpu_copy(&zero, &g_link_received_words[i * 3], 0x05000003);
        }
    }
}
