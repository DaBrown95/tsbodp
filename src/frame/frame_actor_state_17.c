#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_attachment.h"
void frame_actor_state_17(struct FrameObject *object)
{
 unsigned char i;
 struct FramePoint point;
 for(i=0;i<2;i++) {
  unsigned int index=i*4;
  unsigned int base=(unsigned int)object+0x138;
  struct FrameObject **slot=(struct FrameObject **)(base+index);
  if(*slot) {
   unsigned int status=frame_actor_attachment_status(*slot,object);
   if(status==2)frame_detach_actor(object,*slot);
   else if(status==0)frame_detach_actor(object,*slot);
  }
 }
 if(!frame_count_actor_attachments(object)&&((struct FrameActorObject *)object)->state!=23) {
  frame_request_animation((struct FrameCommandObject *)object,1);
  transition_object_set_state(object,((struct FrameActorObject *)object)->default_state);
  frame_set_variant_state(object,2);
  frame_point_to_integer(&object->next_position.word,&point);
  frame_grid_snap_point_to_center(g_frame_registration,&point,&point);
  frame_point_to_fixed(&point,&object->next_position.word);
 }
}
