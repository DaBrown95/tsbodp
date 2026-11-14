#include "link_endpoint_setup.h"

static inline unsigned short serial_record_checksum(struct EventRecord *record)
{
    int sum;
    sum = 0;
    record->storage.fields.reserved = 0;
    {
        register const unsigned char *bytes asm("r1") = (const unsigned char *)record;
        register int index asm("r3") = 0;
        do {
            sum += bytes[index];
        } while (++index <= 11);
    }
    sum += (short)link_current_random_byte();
    link_snapshot_random_byte();
    g_link_word_03007348 = g_link_word_03007354;
    return -sum;
}

void link_prepare_serial_records(struct EventRecord *record,
                                struct EventRecord *received)
{
    int peer;
    register struct EventRecord *received_records asm("r6") = received;
    register struct LinkEndpointSetupPrefix *state asm("r4");
    {
        register struct LinkEndpointSetupPrefix *entry asm("r0") = &g_link_setup_state;
        register unsigned char active asm("r2") = entry->active;
        register int initial_end asm("r1");
        peer = (int)active - 1;
        initial_end = -1;
        state = entry;
        if (peer != initial_end) {
            register struct EventRecord **banks asm("r12") = state->second_records;
            int end = initial_end;
            do {
                unsigned int byte_offset = (unsigned int)peer * sizeof(*received_records);
                int next_peer = peer - 1;
                const unsigned short *from = banks[peer]->storage.halfwords;
                unsigned short *to = ((struct EventRecord *)
                    ((unsigned int)received_records + byte_offset))->storage.halfwords;
                int remaining;
                for (remaining = 5; remaining >= 0; --remaining)
                    *to++ = *from++;
                peer = next_peer;
            } while (peer != end);
        }
    }
    record->storage.fields.reserved = serial_record_checksum(record);
    {
        /* The wide temporary preserves the original R0-to-R4 address transfer
         * with the pinned compiler. Only its low 32 bits form the pointer. */
        register unsigned long long entry asm("r0") = (unsigned int)&g_link_setup_state;
        register struct LinkEndpointSetupPrefix *current asm("r4") =
            (struct LinkEndpointSetupPrefix *)(unsigned int)entry;
        register const unsigned short *from asm("r2") = record->storage.halfwords;
        register unsigned short *to asm("r1") = current->second->storage.halfwords;
        int remaining;
        for (remaining = 5; remaining >= 0; --remaining)
            *to++ = *from++;
        if (current->identifier == -1) {
            struct EventRecord *saved = current->first;
            current->first = current->second;
            current->second = saved;
        }
    }
    g_link_flags &= ~0x40048u;
    g_link_flags |= 0x210;
}
asm(".align 2,0");
