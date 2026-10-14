#include "frame_need_effect_factory.h"
#include "frame_need_effect_placement.h"
#include "resource_object_payload.h"

struct FrameObject *frame_create_need_effect_resource(unsigned char group,unsigned char entry)
{
 struct FrameNeedEffectPayload *payload=(struct FrameNeedEffectPayload *)resource_get_object_payload(group,entry);
 unsigned char *parameters=&payload->kind;
 if(parameters[4]) {
  if(payload->kind==130) {
   unsigned char *world=(unsigned char *)&g_resource_game_state; unsigned char *flags=world+0xe7;
   if(*flags&1)return 0;
   *flags|=1;
  } else if(payload->kind==140) {
   unsigned char *world=(unsigned char *)&g_resource_game_state; unsigned char *flags=world+0xe7;
   if(*flags&2)return 0;
   *flags|=2;
  } else if(actor_entry_collection_group_marked((struct ActorEntryContext *)g_scene_entry_data,g_frame_world_id)==1)return 0;
 }
 if(parameters[0]==33) {
  if(!((struct FrameNeedEffectFactoryWorld *)&g_resource_game_state)->kind33_selector)parameters[0]=33;
  else parameters[0]=34;
 }
 {
  struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)frame_spawn_need_effect(parameters[0],parameters[2],parameters[3],parameters[5],parameters[4]);
  unsigned char *linked=&object->linked;
  unsigned char zero=0;
  *linked=1;
  frame_configure_need_effect((struct FrameObject *)object,parameters[1],payload->x,payload->y);
  *linked=zero;
  return(struct FrameObject *)object;
 }
}
asm(".align 2, 0");
