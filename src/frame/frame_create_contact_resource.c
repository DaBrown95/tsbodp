#include "frame_actor_animation.h"
#include "frame_contact_action.h"
#include "resource_object_payload.h"
#include "transition_object.h"

struct FrameObject *frame_create_contact_resource(unsigned char group,unsigned char entry) {
 unsigned int a=(unsigned char)group,b=(unsigned char)entry;
 struct FrameObject *base=frame_allocate_scene_object();
 const struct ContactActionPayload *payload=(const struct ContactActionPayload *)resource_get_object_payload(a,b);
 struct ContactResourceView *view=(struct ContactResourceView *)base;
 frame_set_position(base,payload->x*65536,payload->y*65536);
 base->id=payload->id;
 base->flags=0x60405;
 view->settings[0]=payload->settings[0];view->settings[1]=payload->settings[1];view->settings[2]=payload->settings[2];view->settings[3]=payload->settings[3];
 transition_object_set_state((struct TransitionObject *)base,0);
 view->contact_mode=0;view->double_size=0;base->display_layer=3;
 frame_acquire_palette_slot(base,2);
 view->on_contact=frame_begin_contact_action;
 view->enabled=1;view->active=1;view->on_step=frame_tick_contact_action;
 frame_set_animation_record(base,&g_contact_action_animation);
 frame_update_actor_state(base);
 return base;
}
asm(".align 2,0");
