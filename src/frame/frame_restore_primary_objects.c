#include "frame.h"
#include "scene_retention.h"
#include "display.h"
void frame_restore_primary_objects(void)
{
 g_frame_primary_list.first=g_frame_retained_primary_list.first;
 g_frame_primary_list.last=g_frame_retained_primary_list.last;
 g_frame_retained_primary_list.first=0;g_frame_retained_primary_list.last=0;
 frame_disable_primary_object_flags(0x02000000);
 display_fill_bytes(g_frame_shared_display,0,572);
}
