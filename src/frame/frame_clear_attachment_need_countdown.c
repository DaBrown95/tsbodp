#include "frame_actor_attachment_parameters.h"
struct FrameAttachmentNeedCountdown { int values[8],countdown; };
void frame_clear_attachment_need_countdown(struct FrameActorNeedState *needs)
{
 if(needs)((struct FrameAttachmentNeedCountdown *)needs)->countdown=0;
}
