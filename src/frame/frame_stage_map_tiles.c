#include "frame_map.h"

void frame_stage_map_tiles(unsigned int view)
{
    unsigned int i;
    for (i = 0; i < 2; i++) {
        struct FrameMapRecord *record = &g_frame_map_records[i];
        if (record->source) {
            register int x asm("r2") = record->origins[(unsigned char)view].x / 32;
            register int y asm("r1") = record->origins[(unsigned char)view].y / 32;
            int cell = y * record->width + x;
            struct FrameMapWordPair *destination = record->staging;
            int columns = record->width - x;
            register int available_rows asm("r3") = record->height - y;
            int rows;
            if (columns > 10) columns = 10;
            rows = available_rows < 7 ? available_rows : 7;
            for (; rows > 0; rows--) {
                register int count asm("r0") = columns;
                for (; count > 0; count--) {
                    register const unsigned short *primary asm("r3") = record->primary;
                    register int cell_byte_offset asm("r1") = cell * 2;
                    unsigned int tile;
                    register const struct FrameMapWordPair *source asm("r3");
                    struct FrameMapWordPair *row_slot;
                    primary += 2;
                    tile = *(const unsigned short *)
                        ((const unsigned char *)primary + cell_byte_offset);
                    source = (const struct FrameMapWordPair *)
                        ((const unsigned char *)record->combined + 4 + (tile << 5));
                    {
                        register struct FrameMapWordPair loaded asm("r1") = *source++;
                        register unsigned int first asm("r1") = loaded.first;
                        register unsigned int second asm("r2") = loaded.second;
                        register struct FrameMapWordPair value asm("r1");
                        value.first = first;
                        value.second = second;
                        destination[0] = value;
                    }
                    {
                        register struct FrameMapWordPair loaded asm("r1") = *source++;
                        register unsigned int first asm("r1") = loaded.first;
                        register unsigned int second asm("r2") = loaded.second;
                        register struct FrameMapWordPair value asm("r1");
                        value.first = first;
                        value.second = second;
                        row_slot = destination + 10;
                        *row_slot = value;
                    }
                    {
                        register struct FrameMapWordPair loaded asm("r1") = *source++;
                        register unsigned int first asm("r1") = loaded.first;
                        register unsigned int second asm("r2") = loaded.second;
                        register struct FrameMapWordPair value asm("r1");
                        value.first = first;
                        value.second = second;
                        row_slot = destination + 20;
                        *row_slot = value;
                    }
                    {
                        register struct FrameMapWordPair loaded asm("r1") = *source;
                        register unsigned int first asm("r1") = loaded.first;
                        register unsigned int second asm("r2") = loaded.second;
                        register struct FrameMapWordPair value asm("r1");
                        value.first = first;
                        value.second = second;
                        row_slot = destination + 30;
                        *row_slot = value;
                    }
                    cell++;
                    destination++;
                }
                destination += 10 - columns;
                destination += 30;
                cell += record->width - columns;
            }
        }
    }
}
