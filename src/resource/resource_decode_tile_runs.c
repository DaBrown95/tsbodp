#include "resource_decode.h"

typedef unsigned char DecoderByte;
typedef unsigned short DecoderHalfword;
typedef unsigned int DecoderWord;

/* A pending byte is paired with the next decoded byte before a halfword write.
 * Complete runs use aligned halfword reads; output can overlap a backward run.
 * The stream terminates with a zero command and has no declared bounds here. */
#define APPEND_BYTE(value) { \
    pending ^= 1; \
    if (pending) { \
        packed = (value); \
    } else { \
        packed = packed | ((DecoderWord)(value) << 8); \
        (*(DecoderHalfword *)cursor = packed, cursor += 2); \
    } \
}

#define COPY_BYTES(read_cursor, length) do { \
    if ((DecoderWord)(read_cursor) & 1) { \
        register DecoderWord byte asm("r14") = *(read_cursor)++; \
        APPEND_BYTE(byte); \
        (length)--; \
    } \
    command = (length) >> 1; \
    if (!pending) { \
        if (!command) { \
            tail = (length) & 1; \
            goto copy_pair_guard_done_1; \
        } \
        tail = (length) & 1; \
        do { \
            DecoderHalfword pair = *(const DecoderHalfword *)(read_cursor); \
            (read_cursor) += 2; \
            *(DecoderHalfword *)cursor = pair; \
            cursor += 2; \
            command--; \
        } while (command); \
copy_pair_guard_done_1: \
        if (tail) { \
            packed = *(read_cursor)++; \
            pending = 1; \
        } \
    } else { \
        if (!command) { \
            tail = (length) & 1; \
            goto copy_pair_guard_done_2; \
        } \
        tail = (length) & 1; \
        do { \
            register DecoderWord pair asm("r14") = *(const DecoderHalfword *)(read_cursor); \
            (read_cursor) += 2; \
            packed |= pair << 8; \
            *(DecoderHalfword *)cursor = packed; \
            cursor += 2; \
            command--; \
            packed = pair >> 8; \
        } while (command); \
copy_pair_guard_done_2: \
        if (tail) { \
            DecoderWord byte = *(read_cursor)++; \
            packed |= byte << 8; \
            *(DecoderHalfword *)cursor = packed; \
            cursor += 2; \
            pending = 0; \
        } \
    } \
} while (0)

#define COPY_LITERAL_BYTES(read_cursor, length) do { \
    if ((DecoderWord)(read_cursor) & 1) { \
        pending ^= 1; \
        if (pending) { \
            packed = *(read_cursor)++; \
        } else { \
            packed |= (DecoderWord)*(read_cursor)++ << 8; \
            *(DecoderHalfword *)cursor = packed; \
            cursor += 2; \
        } \
        (length)--; \
    } \
    command = (length) >> 1; \
    if (!pending) { \
        if (!command) { \
            tail = (length) & 1; \
            goto copy_pair_guard_done_3; \
        } \
        tail = (length) & 1; \
        do { \
            DecoderHalfword pair = *(const DecoderHalfword *)(read_cursor); \
            (read_cursor) += 2; \
            *(DecoderHalfword *)cursor = pair; \
            cursor += 2; \
            command--; \
        } while (command); \
copy_pair_guard_done_3: \
        if (tail) { \
            packed = *(read_cursor)++; \
            pending = 1; \
        } \
    } else { \
        if (!command) { \
            tail = (length) & 1; \
            goto copy_pair_guard_done_4; \
        } \
        tail = (length) & 1; \
        do { \
            register DecoderWord pair asm("r14") = *(const DecoderHalfword *)(read_cursor); \
            (read_cursor) += 2; \
            packed |= pair << 8; \
            *(DecoderHalfword *)cursor = packed; \
            cursor += 2; \
            command--; \
            packed = pair >> 8; \
        } while (command); \
copy_pair_guard_done_4: \
        if (tail) { \
            DecoderWord byte = *(read_cursor)++; \
            packed |= byte << 8; \
            *(DecoderHalfword *)cursor = packed; \
            cursor += 2; \
            pending = 0; \
        } \
    } \
} while (0)

void *resource_decode_tile_runs(const void *data, void *destination,
                               unsigned int *decoded_size)
{
    register const DecoderByte *input = data;
    register DecoderByte *cursor asm("r0") = destination;
    register DecoderWord pending = 0;
    register DecoderWord packed asm("r4");
    register unsigned int *size_output = decoded_size;
    register DecoderWord command asm("r12") = *input++;
    register const DecoderByte *start = destination;
    if (command) {
        do {
            register DecoderWord length asm("r1");
            /* Holds the count field, then distance, then the odd-byte tail. */
            DecoderWord tail;
            if (!(command & 0x80))
                goto short_command;
            {
                register DecoderWord prefix asm("r3") = command & 0x7f;
                DecoderWord scaled_prefix;
                register DecoderWord low asm("r2");
                command = *input++;
                scaled_prefix = prefix << 3;
                tail = command & 0x1f;
                length = tail + 2;
                low = command >> 5;
                if (length != 2) {
                    tail = scaled_prefix | low;
                    goto backreference_setup;
                }
                tail = scaled_prefix | low;
                length = tail + 0x42;
                goto repeat_bytes;
backreference_setup:
                {
                    register const DecoderByte *previous = (DecoderByte *)cursor + pending - tail;
                    COPY_BYTES(previous, length);
                }
                goto next_command;
            }
short_command:
            if (!(command & 0x40))
                goto literal_bytes;
            { register DecoderWord repeat_count_field asm("r3") = command & 0x3f;
              length = repeat_count_field + 3; }
repeat_bytes:
            command = *input++;
            if (pending) {
                packed |= command << 8;
                length--;
                *(DecoderHalfword *)cursor = packed;
                cursor += 2;
            }
            packed = command | (command << 8);
            command = length >> 1;
            if (!command) {
                tail = length & 1;
                goto repeat_pairs_done;
            }
            tail = length & 1;
            do {
                *(DecoderHalfword *)cursor = packed;
                cursor += 2;
                command--;
            } while (command);
repeat_pairs_done:
            pending = tail;
            if (pending)
                packed &= 0xff;
            goto next_command;
literal_bytes:
            length = command;
            COPY_LITERAL_BYTES(input, length);
next_command:
            command = *input++;
        } while (command);
    }
    if (pending)
        *cursor++ = packed;
    *size_output = cursor - start;
    return cursor;
}
