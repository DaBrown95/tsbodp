#include "frame_indicator.h"
#include "resource_object_payload.h"
#include "frame_palette_resource.h"
struct FrameObject *frame_create_palette_resource(unsigned char group,unsigned char entry) {
 const struct FramePaletteResourcePayload *payload=(const struct FramePaletteResourcePayload *)resource_get_object_payload(group,entry);
 struct FrameObject *base=frame_allocate_object(payload->id);
 struct FramePaletteResourceView *object=(struct FramePaletteResourceView *)base;
 frame_set_position(base,payload->x*65536,payload->y*65536);
 object->actor_id=0;
 object->direction=0;
 object->flags=0x40019;
 frame_set_animation_record(base,&g_frame_palette_resource_animation);
 transition_object_set_state(base,0);
 frame_acquire_palette_slot(base,payload->palette);
 object->on_step=frame_palette_resource_step;
 object->contact[0]=0;object->contact[1]=0;
 object->contact_mode=0;object->double_size=0;
 frame_update_actor_state(base);
 return base;
}
