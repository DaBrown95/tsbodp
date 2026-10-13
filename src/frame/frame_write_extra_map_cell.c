#include "frame_map_animation.h"

void frame_write_extra_map_cell(unsigned short x,unsigned short y,unsigned short source_index) {
 struct FramePoint dimensions;
 unsigned short *cell;
 unsigned int value;
 frame_get_map_dimensions(&dimensions);
 cell=(unsigned short *)g_frame_map_extra_cell_types+((x>>5)+(y>>5)*(dimensions.x>>5));
 value=g_frame_map_cell_header;
 value+=*((unsigned short *)g_frame_map_extra_cell_types+g_frame_map_cell_count+source_index);
 *cell=value;
}
asm(".align 2, 0");
