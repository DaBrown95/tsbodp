#include "frame_map_scene.h"
#include "frame_grid_cells.h"
extern void *scene_fill_bytes(void *,int,unsigned int);
void frame_destroy_map_registration(void *base)
{
 struct FrameMapRegistration *context=base;
 scene_fill_bytes(context->data,0,1);
 heap_free(context->data);
 scene_fill_bytes(context,0,20);
 heap_free(context);
}
asm(".align 2, 0");
