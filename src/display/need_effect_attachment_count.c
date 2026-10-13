#include "display_need_effect_lifecycle.h"
unsigned int frame_need_effect_attachment_count(struct FrameNeedEffectState *state)
{
 struct FrameActorAttachmentRecord *record;
 unsigned int count=0,index=0;
 record=((struct DisplayNeedEffectStateView *)state)->records;
 do {
  if(record->actor)count++;
  record++;
  index++;
 }while(index<3);
 return count;
}
