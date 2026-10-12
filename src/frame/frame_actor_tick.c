#include "frame_actor_runtime.h"
void frame_actor_tick(struct FrameObject *base)
{
 struct FrameActorObject *object = (struct FrameActorObject *)base;
 if (!object->state) frame_request_animation((struct FrameCommandObject *)object, 1);
 else frame_run_actor_state((struct FrameObject *)object);
 if (object->subtype > 31) frame_update_actor_parts((struct FrameObject *)object);
 else frame_update_actor_animation((struct FrameObject *)object);
 if (object->subtype > 17) {
  if (frame_actor_indicator_kind((FrameU8)(object->subtype - 18)) != 0xff && object->variant_state != 41) {
   if (!object->indicator) object->indicator = frame_create_actor_indicator((struct FrameObject *)object, 8, 0);
  } else if (object->indicator) {
   transition_object_set_state(object->indicator, 1);
   object->indicator = 0;
  }
 }
 if (object->direction > 4) object->oam.flip_x = 1;
 else object->oam.flip_x = 0;
 object->pending_updates = 0;
 frame_update_actor_state((struct FrameObject *)object);
}
