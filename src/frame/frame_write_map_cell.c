#include "frame_map.h"
void frame_write_map_cell(unsigned int index, unsigned short x, unsigned short y, unsigned int source_index) {
 struct FrameMapRecord *record=&g_frame_map_records[index];
 unsigned short value=((unsigned short *)record->secondary)[source_index+2];
 unsigned short *cell=frame_map_cell(index,x,y);
 *cell=value+*(unsigned int *)record->combined;
}
asm(".align 2, 0");
