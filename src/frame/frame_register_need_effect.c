#include "frame_need_effect_registration.h"
static inline unsigned char read_pattern_action(const unsigned char *actions,
                                                unsigned int x,unsigned int y)
{
 unsigned int row=y*5;
 unsigned int column=x;
 return actions[column+row];
}
unsigned char frame_register_need_effect(void *context,struct FrameObject *base,unsigned char commit)
{
 unsigned int x=0,y=0;
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
 struct FrameNeedEffectState *state=object->effect_state;
 const unsigned char *pattern=g_need_effect_action_sets[object->kind];
 struct FramePoint position={((short *)&object->position.x)[1],((short *)&object->position.y)[1]};
 unsigned int direction=object->direction;
 unsigned char candidate_count,target_count;
 struct FramePoint near_bounds,far_bounds;
 unsigned char linked=object->linked;

 struct FrameActorPackedCell anchor,cell;
 /* This cell output pointer remains live across the scan's calls. */
 register struct FrameActorPackedCell *cell_pointer asm("r5");

 const unsigned char *actions;
 unsigned char available;
 candidate_count=0;
 if(commit==1) {
  if(frame_register_need_effect(context,base,0)!=1)return 0;
  heap_clear((unsigned char *)state+0x74,0,104);
  object->mode=commit;
 }
 if(!frame_grid_point_to_cell(context,&position,&anchor))return 0;
 available=1; target_count=0;
 x=0;cell_pointer=&cell;actions=pattern+2;
 for(;x<5;x++) {
  for(y=0;y<5;y++) {
   unsigned char action;
   frame_need_effect_pattern_cell(x,y,pattern,direction,&anchor,cell_pointer);
   action=read_pattern_action(actions,x,y);
   switch(action) {
   case 0:break;
   case 1:
    available=frame_grid_need_effect_cell_available(context,cell_pointer,1,linked);
    if(commit==1&&available==1)frame_grid_add_occupancy(context,cell_pointer,1);
    break;
   case 2:
    available=frame_grid_need_effect_cell_available(context,cell_pointer,2,linked);
    if(commit==1&&available==1) {
     struct FrameNeedEffectState *neighbor=frame_need_effect_find_neighbor(cell_pointer,3);
     if(neighbor) {
      struct FrameObject *neighbor_object;
      frame_need_effect_increment_counter(neighbor,state);
      neighbor_object=((struct DisplayNeedEffectStateView *)neighbor)->object;
      neighbor_object->spatial.bounds.upper=
       ((struct FrameNeedEffectSpatialWork *)((struct FrameNeedEffectObject *)neighbor_object)->effect_state)->far_bounds;
      frame_need_effect_handoff_bounds(((struct DisplayNeedEffectStateView *)state)->object,neighbor,1);
     }
     frame_grid_add_occupancy(context,cell_pointer,8);
     frame_grid_remove_occupancy(context,cell_pointer,4);
    }
    break;
   case 3:
    available=frame_grid_need_effect_cell_available(context,cell_pointer,3,linked);
    if(commit==1&&available==1) {
     if(frame_grid_occupancy(context,(const int *)cell_pointer)&8) {
      struct FrameNeedEffectState *neighbor=frame_need_effect_find_neighbor(cell_pointer,2);
      struct FrameObject *neighbor_object;
      frame_need_effect_increment_counter(state,neighbor);
      neighbor_object=((struct DisplayNeedEffectStateView *)neighbor)->object;
      neighbor_object->spatial.bounds.upper=
       ((struct FrameNeedEffectSpatialWork *)((struct FrameNeedEffectObject *)neighbor_object)->effect_state)->far_bounds;
      frame_need_effect_handoff_bounds(((struct DisplayNeedEffectStateView *)neighbor)->object,neighbor,1);
     } else frame_grid_add_occupancy(context,cell_pointer,4);
    }
    break;
   case 4:
    available=frame_grid_need_effect_cell_available(context,cell_pointer,4,linked);
    if(commit==1&&available==1) {
     frame_grid_add_occupancy(context,cell_pointer,2);
     ((struct FrameNeedEffectSpatialWork *)state)->candidates[candidate_count].x=((unsigned char *)cell_pointer)[0];
     ((struct FrameNeedEffectSpatialWork *)state)->candidates[candidate_count].y=((unsigned char *)cell_pointer)[1];
     candidate_count++;
    }
    break;
   case 5:
    available=frame_grid_need_effect_cell_available(context,cell_pointer,5,linked);
    if(commit==1&&available==1)frame_grid_add_occupancy(context,cell_pointer,1);
    break;
   }
   if(!available)return 0;
   action=read_pattern_action(actions,x,y);
   if(action==1||action==3||action==5||action==2) {
    ((struct FrameNeedEffectSpatialWork *)state)->targets[target_count].x=((unsigned char *)cell_pointer)[0];
    ((struct FrameNeedEffectSpatialWork *)state)->targets[target_count].y=((unsigned char *)&cell)[1];
    target_count++;
   }
  }
 }
 if(commit==1) {

  struct FramePoint first,last;
  unsigned char i;
  near_bounds.x=5000;near_bounds.y=0;far_bounds.x=0;far_bounds.y=5000;
  if(target_count==0) {
   for(i=0;i<candidate_count;i++) {
    frame_grid_cell_extents(context,(const int *)&((struct FrameNeedEffectSpatialWork *)state)->candidates[i],&first,&last);
    if(first.x<near_bounds.x)near_bounds.x=first.x;
    if(first.y>near_bounds.y)near_bounds.y=first.y;
    if(last.x>far_bounds.x)far_bounds.x=last.x;
    if(last.y<far_bounds.y)far_bounds.y=last.y;
   }
  } else {
   for(i=0;i<target_count;i++) {
    frame_grid_cell_extents(context,(const int *)&((struct FrameNeedEffectSpatialWork *)state)->targets[i],&first,&last);
    if(first.x<near_bounds.x)near_bounds.x=first.x;
    if(first.y>near_bounds.y)near_bounds.y=first.y;
    if(last.x>far_bounds.x)far_bounds.x=last.x;
    if(last.y<far_bounds.y)far_bounds.y=last.y;
   }
  }
  ((struct FrameNeedEffectSpatialWork *)state)->far_bounds=far_bounds;
  ((struct FrameNeedEffectSpatialWork *)state)->near_bounds=near_bounds;
 }
 return 1;
}
