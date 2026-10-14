#include "frame_actor_animation.h"
#include "frame_contact_action.h"
#include "display_time_format.h"
#include "display_text_fields.h"
#include "resource_conditions.h"
#include "scene_request.h"

extern struct SceneRequest g_scene_previous_request;

void frame_tick_contact_action(struct FrameObject *base) {
 struct ContactTickView *object=(struct ContactTickView *)base;
 char buffer[20];
 union ContactClock first,second;
 unsigned int success;
 first.record=g_resource_selector_clock;
 second.record=g_resource_selector_clock;
 success=0;
 switch(object->state) {
 case 0:break;
 case 4:
  first.fields.hour=object->first_hour;
  second.fields.hour=object->second_hour;
  if(!(unsigned char)condition_group_complete(g_contact_action_conditions[object->kind].row,g_contact_action_conditions[object->kind].column)) {
   g_contact_action_messages[0]=0x1857;
  } else if((g_contact_action_world.completed>>object->kind)&1) {
   g_contact_action_messages[0]=0x1855;
  } else if(frame_actor_need_average((struct FrameActorNeedState *)g_contact_action_world.needs)<=30) {
   g_contact_action_messages[0]=0x1858;
  } else if((unsigned char)display_time_in_range(&first.record,&second.record,&g_contact_action_world.clock,6)) {
   success=1;
   g_contact_action_messages[0]=0x1854;
   g_contact_action_messages[1]=210;
   g_contact_action_messages[2]=211;
   g_contact_action_notice.confirmed=1;
  } else {
   g_contact_action_messages[0]=0x1856;
   first.record.hour=object->first_hour;
   display_time_format(&first.record,buffer,0x1851);
   display_text_copy_field_one(buffer);
   second.record.hour=object->second_hour;
   display_time_format(&second.record,buffer,0x1851);
   display_text_copy_field_two(buffer);
  }
  g_contact_action_notice.active=0;
  g_contact_action_notice.mode=1;
  g_contact_action_notice.kind=4;
  display_text_copy_field_zero(display_scene_lookup_text(object->kind+0x1859));
  scene_submit_default_request(2);
  if(!success) {
   frame_set_actor_direction(object->partner,4);
   frame_request_animation((struct FrameCommandObject *)object->partner,0x55);
   frame_set_variant_state(object->partner,0x36);
  }
  object->state=5;
  break;
 case 5:
  if(g_scene_previous_request.parameter==1) {
   g_scene_mode_bytes[0]=object->parameter;
   resource_submit_scene(20,object->kind,g_contact_action_world.values[object->kind]);
   g_contact_action_world.completed|=1<<object->kind;
  } else {
   ((struct ContactTickView *)object->partner)->state=16;
   object->partner=0;
   object->state=0;
  }
  break;
 }
}
asm(".align 2,0");
