#include "frame_need_effect_placement.h"
void frame_unregister_need_effect(void *context,struct FrameObject *base)
{
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
 const unsigned char *pattern;
 struct FramePoint position;
 unsigned int direction,x,y,next_x;
 const unsigned char *actions;
 struct FrameActorPackedCell anchor,cell;
 object->mode=0;
 pattern=g_need_effect_action_sets[object->kind];
 position.x=((short *)&object->position.x)[1];position.y=((short *)&object->position.y)[1];
 direction=object->direction;
 if(!frame_grid_point_to_cell(context,&position,&anchor))return;
 x=0;
 for(;x<=4;x=next_x) {
  y=0;next_x=x+1;
  for(;y<=4;y++) {
   unsigned char action;
   frame_need_effect_pattern_cell(x,y,pattern,direction,&anchor,&cell);
   actions=pattern+2;action=actions[y*5+x];
   switch(action) {
   case 0:break;
   case 1:case 5:
    frame_unregister_bounds(context,&cell,1);break;
   case 2: {
    struct FrameNeedEffectState *neighbor=frame_need_effect_find_neighbor(&cell,3);
    if((unsigned char)(neighbor!=0)==1) {
     frame_need_effect_decrement_counter(neighbor,object->effect_state);
     frame_register_bounds(context,&cell,4);
    }else frame_unregister_bounds(context,&cell,61);
    break;
   }
   case 3:
    frame_unregister_bounds(context,&cell,13);break;
   case 4: {
    unsigned char shared=0;
    /* Current state is last read before each call; cached next survives it. */
    register struct FrameNeedEffectState *state asm("r2")=(struct FrameNeedEffectState *)g_frame_need_effect_active_list.first;
    while(state) {
     struct FrameNeedEffectState *next=((struct DisplayNeedEffectStateView *)state)->next;
     if(((struct DisplayNeedEffectStateView *)state)->object!=(struct FrameObject *)object && frame_need_effect_contains_candidate(state,&cell)==1)shared=1;
     state=next;
    }
    if(!shared)frame_unregister_bounds(context,&cell,2);
    break;
   }
   }
  }
 }
}
