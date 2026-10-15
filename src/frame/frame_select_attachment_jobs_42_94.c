#include "frame_actor_attachment_jobs_42_94_callbacks.h"
unsigned int frame_select_attachment_jobs_42_94(struct FrameNeedEffectState *owner,unsigned char *choices)
{
 choices[0]=42;
 if(g_scene_id!=41)choices[1]=94;
 return 1;
}
