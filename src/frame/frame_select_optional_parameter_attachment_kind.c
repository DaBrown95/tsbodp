#include "frame_need_effect_optional_completion.h"
unsigned int frame_select_optional_parameter_attachment_kind(struct FrameNeedEffectState *owner,unsigned char *out)
{
 if((unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe,1)<=1)*out=55;
 else *out=7;
 return 1;
}
