#include "scene_resume.h"
#include "frame.h"
#include "display.h"
void scene_clear_shared_display(void)
{
 display_fill_bytes(g_frame_shared_display,0,572);
}
