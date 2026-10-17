#include "frame_grid_selection.h"
void frame_grid_selection_mark_attachments(struct FrameObject *base)
{
 if(g_input_pressed[g_input_config.local_player]&2) {
  unsigned char i;
  for(i=0;i<2;i++) {
   struct FrameObject *owner=((struct FrameActorAttachmentView *)base)->slots[i];
   if(owner)frame_need_effect_mark_attachment_running((struct FrameNeedEffectState *)owner,base);
  }
 }
}
asm(".align 2,0");
