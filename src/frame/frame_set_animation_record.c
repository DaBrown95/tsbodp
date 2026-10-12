#include "frame_actor_animation.h"
void frame_set_animation_resource(struct FrameObject *, struct FrameSpriteResource *);
void display_load_palette_alternate(const void *, FrameU32, FrameU32);
void display_queue_palette(const void *, FrameU32, FrameU32);
void frame_set_animation_record(struct FrameObject *base, struct FrameVariantResource *resource)
{
 struct FrameTickObject *object = (struct FrameTickObject *)base;
 object->frame_delay = resource->frame_delay;
 frame_set_animation_resource(base, (struct FrameSpriteResource *)resource);
 if (resource->palette) {
  if (g_frame_flags & 0x10)
   display_load_palette_alternate(resource->palette, object->display.oam.palette * 16, 16);
  else
   display_queue_palette(resource->palette, object->display.oam.palette * 16, 16);
 }
}
