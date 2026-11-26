#include "link_serial_handshake.h"

#define SERIAL_IDENTIFIER (*(volatile int *)&g_link_setup_state.identifier)

static inline void serial_restart_host(void)
{
    if ((signed char)g_link_setup_state.slot == 0) {
        HANDSHAKE_CONTROL |= 0x80;
        HANDSHAKE_TIMER = 0xc0;
    }
}

static inline unsigned char serial_sum_is_zero(int value)
{
    register int observed asm("r0") = value;
    if ((short)observed == 0)
        return 1;
    return 0;
}

/* The checksum accumulator reuses the flags pointer's register during validation. */
union SerialTransferWork {
    int sum;
    volatile unsigned int *flags;
};

void link_serial_interrupt(void)
{
    register volatile unsigned int *incoming_flags asm("r0");
    register union SerialTransferWork transfer;
    unsigned int initial_flags;
    int peer;
    int transfer_peer;
    int ready;

    if (HANDSHAKE_CONTROL & 0x80)
        return;
    if (HANDSHAKE_CONTROL & 0x40) {
        ++g_link_clock_03002178;
        HANDSHAKE_SEND = 0xdead;
        serial_restart_host();
        g_link_flags |= 0x400;
        if (g_link_setup_state.callback)
            g_link_setup_state.callback();
        return;
    }
    incoming_flags = &g_link_flags;
    initial_flags = *incoming_flags & 8;
    transfer.flags = incoming_flags;
    /* Negotiate readiness before exchanging event records. */
    if (initial_flags) {
        if (HANDSHAKE_RECEIVE(0) == 0xdead || HANDSHAKE_RECEIVE(1) == 0xdead ||
            HANDSHAKE_RECEIVE(2) == 0xdead || HANDSHAKE_RECEIVE(3) == 0xdead) {
            ready = 1;
            for (peer = 0; peer < g_link_setup_state.active; peer++) {
                if (HANDSHAKE_RECEIVE(peer) != 0xdead) {
                    ready = 0;
                    break;
                }
            }
            *transfer.flags &= ~0x40000u;
            if (ready) {
                HANDSHAKE_SEND = 0xbeef;
                *transfer.flags |= 0x110;
                *transfer.flags &= ~0x48u;
            } else
                HANDSHAKE_SEND = 0xdead;
            serial_restart_host();
            return;
        }
        if ((signed char)g_link_setup_state.slot == 0) {
            ready = 1;
            if (!(*transfer.flags & 0x40000)) {
                for (peer = 1; peer < g_link_setup_state.active; peer++) {
                    if (HANDSHAKE_RECEIVE(peer) != 0xc0de) {
                        ready = 0;
                        break;
                    }
                }
                if (ready) {
                    *transfer.flags |= 0x40000;
                    HANDSHAKE_SEND = 0xbabe;
                } else
                    HANDSHAKE_SEND = 0xc0de;
                serial_restart_host();
                return;
            }
            for (peer = 1; peer < g_link_setup_state.active; peer++) {
                if (HANDSHAKE_RECEIVE(peer) != 0xbabe) {
                    ready = 0;
                    break;
                }
            }
            if (ready) {
                HANDSHAKE_TIMER = 0;
                link_prepare_serial_records(&g_event_record, g_link_received_events);
                return;
            }
            HANDSHAKE_SEND = 0xbabe;
            serial_restart_host();
            return;
        }
        if (!(*transfer.flags & 0x40000)) {
            if (HANDSHAKE_RECEIVE(0) == 0xc0de) {
                *transfer.flags |= 0x40000;
                HANDSHAKE_SEND = 0xc0de;
            } else
                HANDSHAKE_SEND = 0xbeef;
            return;
        }
        if (HANDSHAKE_RECEIVE(0) == 0xbabe) {
            HANDSHAKE_SEND = 0xbabe;
            link_prepare_serial_records(&g_event_record, g_link_received_events);
        } else
            HANDSHAKE_SEND = 0xc0de;
        return;
    }
    if (SERIAL_IDENTIFIER == -1 &&
        (HANDSHAKE_RECEIVE(0) == 0xdead || HANDSHAKE_RECEIVE(1) == 0xdead ||
         HANDSHAKE_RECEIVE(2) == 0xdead || HANDSHAKE_RECEIVE(3) == 0xdead)) {
        ready = 1;

        for (peer = 0; peer < g_link_setup_state.active; peer++) {
            if (HANDSHAKE_RECEIVE(peer) != 0xdead) {
                ready = 0;
                break;
            }
        }
        if (ready) {
            HANDSHAKE_SEND = 0xbeef;
            SERIAL_IDENTIFIER = -1;
            *transfer.flags &= ~0x400u;
            *transfer.flags |= 0x100;
            g_link_transfer_retry_count = 0;
        } else
            HANDSHAKE_SEND = 0xdead;
        serial_restart_host();
        return;
    }
    if (g_link_transfer_retry_count > 5) {
        HANDSHAKE_SEND = 0xdead;
        serial_restart_host();
        return;
    }
    if (!(*transfer.flags & 0x40)) {
        /* Record transfers advance one 16-bit word per interrupt. */
        if (SERIAL_IDENTIFIER > -1) {
            transfer_peer = g_link_setup_state.active;
            for (--transfer_peer; transfer_peer != -1; transfer_peer--) {
                unsigned int unit = (unsigned int)SERIAL_IDENTIFIER;
                struct EventRecord *received = g_link_setup_state.first_records[transfer_peer];
                *(unsigned short *)((unsigned int)received + 2 * unit) =
                    HANDSHAKE_RECEIVE(transfer_peer);
            }
            ++g_link_word_0300734c;
        } else {
            if ((signed char)g_link_setup_state.slot != 0 && HANDSHAKE_RECEIVE(0) == 0xbabe) {
                HANDSHAKE_SEND = 0xbabe;
                return;
            }
            transfer_peer = g_link_setup_state.active;
            for (--transfer_peer; transfer_peer != -1; transfer_peer--) {
                if (HANDSHAKE_RECEIVE(transfer_peer) != 0xbeef &&
                    HANDSHAKE_RECEIVE(transfer_peer) != 0xbabe) {
                    g_link_flags |= 0x400;
                    HANDSHAKE_SEND = 0xdead;
                    serial_restart_host();
                    return;
                }
            }
        }
        ++SERIAL_IDENTIFIER;
        if (SERIAL_IDENTIFIER <= 5) {
            volatile unsigned short *send = (volatile unsigned short *)0x0400012a;
            unsigned int unit = (unsigned int)SERIAL_IDENTIFIER;
            const struct EventRecord *record = g_link_setup_state.first;
            *send = *(const unsigned short *)((unsigned int)record + 2 * unit);
            serial_restart_host();
            return;
        }
        {
            int completed_peer;
            int records_valid;
            struct EventRecord *saved_record;
            register volatile unsigned int *status asm("r5");

            /* Check each record with its checksum word temporarily cleared. */
            records_valid = 1;
            for (completed_peer = 0; completed_peer < g_link_setup_state.active; ++completed_peer) {
                struct EventRecord *checksum_record =
                    g_link_setup_state.first_records[completed_peer];
                int total;
                unsigned int checksum_byte;
                int checksum;
                const unsigned char *bytes;
                transfer.sum = 0;
                checksum = (short)checksum_record->storage.fields.reserved;
                checksum_record->storage.fields.reserved = transfer.sum;
                bytes = (const unsigned char *)checksum_record;
                for (checksum_byte = 0; checksum_byte < sizeof(*checksum_record); ++checksum_byte)
                    transfer.sum += bytes[checksum_byte];
                transfer.sum += (short)link_saved_random_byte();
                checksum_record->storage.fields.reserved = checksum;
                total = transfer.sum + checksum;
                if (!serial_sum_is_zero(total)) {
                    records_valid = 0;
                    break;
                }
            }

            if (records_valid && !(g_link_flags & 0x400)) {
                status = &g_link_flags;
                SERIAL_IDENTIFIER = -1;
                g_link_transfer_retry_count = 0;
                *status |= 0x40;
                *status &= ~0x100u;
                ++g_link_word_0300733c;
                g_link_last_serial_vblank = g_irq_context->vblank_count;
                completed_peer = 0;
                if (completed_peer < g_link_setup_state.active) {
                    do {
                        saved_record = g_link_setup_state.first_records[completed_peer];
                        g_link_setup_state.first_records[completed_peer] =
                            g_link_setup_state.second_records[completed_peer];
                        g_link_setup_state.second_records[completed_peer] = saved_record;
                        ++completed_peer;
                    } while (completed_peer < g_link_setup_state.active);
                }
                if ((signed char)g_link_setup_state.slot == 0)
                    HANDSHAKE_TIMER = 0;
                HANDSHAKE_SEND = 0xbeef;
                return;
            }
            transfer.flags = &g_link_flags;
            {
                struct LinkEndpointSetupPrefix *failed_setup = &g_link_setup_state;
                ++g_link_word_03007344;
                ++g_link_transfer_retry_count;
                *transfer.flags |= 0x100;
                *transfer.flags &= ~0x440u;
                (*(volatile int *)&failed_setup->identifier) = -1;
                HANDSHAKE_SEND = 0xdead;
                if ((signed char)failed_setup->slot == 0) {
                    HANDSHAKE_CONTROL |= 0x80;
                    HANDSHAKE_TIMER = 0xc0;
                }
            }
        }
    } else {
        if ((signed char)g_link_setup_state.slot != 0 && SERIAL_IDENTIFIER == 0 &&
            HANDSHAKE_RECEIVE(0) == 0xb0ca)
            HANDSHAKE_SEND = 0xb0ca;
        return;
    }
}
