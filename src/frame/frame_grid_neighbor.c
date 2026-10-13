#include "frame_map_scene.h"
#include "frame_actor_target_cells.h"

extern void *display_text_copy_bytes(void *, const void *, unsigned int);

unsigned char frame_grid_neighbor(void *base, const int *cell, int *output, unsigned char direction)
{
 struct FrameMapRegistration *context=base;
 unsigned char offsets[8][2];

 display_text_copy_bytes(offsets,g_frame_grid_neighbor_offsets,16);
 ((unsigned char *)output)[0]=((const unsigned char *)cell)[0]+offsets[direction][0];
 ((unsigned char *)output)[1]=((const unsigned char *)cell)[1]+offsets[direction][1];
 if(((unsigned char *)output)[0]>=context->extent || ((unsigned char *)output)[1]>=context->extent)return 0;
 return 1;
}
asm(".align 2, 0");
