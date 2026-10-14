#include "frame_actor_action_target.h"
unsigned char frame_find_action_target(struct FrameObject *actor,unsigned int action,void **target)
{
 struct FrameActionSearchNode *node=(struct FrameActionSearchNode *)g_frame_pending_action_head;
 while(node) {
  struct FrameActionSearchNode *next=node->next;
  if(g_frame_action_search_descriptors[node->kind].enabled && node->check(node,actor)) {
   unsigned char actions[7];
   unsigned char i;
   scene_fill_bytes(actions,0,7);
   node->actions((struct FrameNeedEffectState *)node,actions);
   for(i=0;i<7;i++) {
    unsigned char code=actions[i];
    if(code) {if(code==action){*target=node->target;return 1;}}
    else break;
   }
  }
  node=next;
 }
 return 0;
}
asm(".align 2, 0");
