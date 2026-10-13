#include "scene_environment.h"
void scene_allocate_retained_palette(void)
{
 g_scene_context.palette=heap_allocate_zeroed(512);
 g_scene_id=50;
}
