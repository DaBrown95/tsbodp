#include "frame_map.h"
unsigned short *frame_map_cell(unsigned int index, unsigned int x, unsigned int y) {
 struct FrameMapRecord *record=&g_frame_map_records[index];
 unsigned short cell, column, row;
 column = x >> 5;
 row = y >> 5;
 cell = column + row * record->width;
 return (unsigned short *)((unsigned char *)record->primary + (cell * 2 + 4));
}
asm(".align 2, 0");
