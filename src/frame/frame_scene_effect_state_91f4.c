#include "frame_scene_effect.h"
void frame_scene_effect_state_91f4(struct FrameObject *base) {
 struct FrameSceneEffectWork *object=(struct FrameSceneEffectWork *)base;
 int primary=0,extended=0;
 if((unsigned char)(object->kind-2)<=1 || object->kind==5)primary=1;
 if(object->kind==3 || object->kind==1 || object->kind==5 || object->kind==4)extended=1;
 switch(object->variant_state) {
 case 0:{
  unsigned int count=0,i;
  if(primary==1) {
   g_frame_scene_effect_menu_labels[0]=6112;
   g_frame_scene_effect_menu_actions[0]=39;
   count=1;
   if(object->partner==object->owner) {
    g_frame_scene_effect_menu_labels[1]=6108;
    g_frame_scene_effect_menu_actions[1]=35;
    count=2;
   }
  }
  g_frame_scene_effect_menu_labels[count]=6109;
  g_frame_scene_effect_menu_actions[count]=36;
  count++;
  if(extended==1) {
   g_frame_scene_effect_menu_labels[count]=6110;
   g_frame_scene_effect_menu_actions[count]=37;
   count++;
  }
  if(object->partner==object->owner) {
   g_frame_scene_effect_menu_labels[count]=6113;
   g_frame_scene_effect_menu_actions[count]=40;
   count++;
  }
  g_actor_scene_request.active=0;
  for(i=0;i<count;i++)((unsigned short*)&g_actor_scene_result_id)[i]=g_frame_scene_effect_menu_labels[i];
  ((struct FrameSceneEffectRequest*)&g_actor_scene_request)->reset1=0;
  ((struct FrameSceneEffectRequest*)&g_actor_scene_request)->reset2=0;
  resource_scene_event(2);
  frame_set_variant_state((struct FrameObject *)object,55);
  break;
 }
 case 55:{
  int selected=((struct FrameSceneEffectMenuSelection*)&g_resource_scene_arg)->selection;
  if(selected!=-1) {
   switch(g_frame_scene_effect_menu_actions[selected]) {
   case 39:
    transition_object_set_state((struct FrameObject *)object,29);
    frame_set_variant_state((struct FrameObject *)object,27);
    frame_scene_effect_configure((struct FrameObject *)object,1);
    object->timer=300;
    break;
   case 35:
    transition_object_set_state((struct FrameObject *)object,29);
    frame_set_variant_state((struct FrameObject *)object,28);
    object->timer=1800;
    break;
   case 36:
    transition_object_set_state(object->partner,0);
    frame_request_animation((struct FrameCommandObject *)object->partner,29);
    transition_object_set_state((struct FrameObject *)object,29);
    frame_set_variant_state((struct FrameObject *)object,30);
    frame_scene_effect_configure((struct FrameObject *)object,2);
    object->timer=150;
    break;
   case 37:
    transition_object_set_state(object->partner,0);
    frame_request_animation((struct FrameCommandObject *)object->partner,46);
    transition_object_set_state((struct FrameObject *)object,29);
    frame_set_variant_state((struct FrameObject *)object,31);
    frame_scene_effect_configure((struct FrameObject *)object,3);
    object->timer=150;
    break;
   case 40:
    transition_object_set_state(object->partner,0);
    frame_request_animation((struct FrameCommandObject *)object->partner,32);
    frame_set_variant_state((struct FrameObject *)object,14);
    object->timer=8;
    break;
   }
  } else {
   transition_object_set_state((struct FrameObject *)object,29);
   frame_set_variant_state((struct FrameObject *)object,7);
  }
  break;
 }
 case 14:
  if(--object->timer==-1) {
   unsigned char added;
   frame_set_variant_state((struct FrameObject *)object,15);
   added=(unsigned char)actor_entry_add(((struct FrameSceneEffectActorEntryView*)&g_frame_scene_actor_selection)->entries,g_frame_scene_actor_selection.saved_effect_kind+195,0,0);
   g_frame_scene_actor_selection.world=50;
   if(added==1)frame_disable_object_flags((struct FrameObject *)object,1);
   else {
    transition_object_set_state((struct FrameObject *)object,29);
    frame_set_variant_state((struct FrameObject *)object,7);
    transition_object_set_state(object->partner,((struct FrameActorObject *)object->partner)->default_state);
    frame_set_variant_state(object->partner,2);
    ((struct FrameSceneEffectUi*)&g_scene_mode_flags)->views[g_input_config.local_player].changed|=0x200000;
   }
  }
  break;
 case 15:
  if(object->partner->flags&0x400000) {
   transition_object_set_state((struct FrameObject *)object,1);
   frame_enable_object_flags((struct FrameObject *)object,2);
   transition_object_set_state(object->partner,((struct FrameActorObject *)object->partner)->default_state);
   frame_set_variant_state(object->partner,2);
   g_frame_scene_actor_selection.world=50;
  }
  break;
 }
}
