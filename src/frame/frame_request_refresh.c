#include "frame.h"
extern FrameU8 g_frame_force_refresh;
extern int frame_schedule(struct FrameObjectList *, FrameU8);
FrameU8 frame_request_refresh(void) {
 g_frame_force_refresh=1;
 return frame_schedule(&g_frame_primary_list,1);
}
