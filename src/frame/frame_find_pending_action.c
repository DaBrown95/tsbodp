#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_choices.h"
unsigned char frame_find_pending_action(unsigned int category,struct FrameObject **target,unsigned int *action)
{
 unsigned int match=0;
 struct FramePendingAction *node=g_frame_pending_action_head;
 while(node) {
  struct FramePendingAction *next=node->next;
  unsigned char code=node->action;
  if(code) {
   switch(category) {
   case 1:if(code==12||code==27)match=1;break;
   case 2:if(code==45)match=1;break;
   case 3:if(code==22)match=1;break;
   }
   if(match==1) {*action=node->action;node->action=0;*target=node->target;return 1;}
  }
  node=next;
 }
 return 0;
}
