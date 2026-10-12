#include "frame_tick.h"
struct FramePartRecord { const FrameU8 *data; struct FrameSpriteSequence *sequence; const FrameU8 *palette; FrameU8 frame_delay, unknown_0d[3]; };
void frame_set_animation_resource(struct FrameObject *, struct FrameSpriteResource *);
void display_load_palette_alternate(const void *, FrameU32, FrameU32);
void display_queue_palette(const void *, FrameU32, FrameU32);
void frame_set_animation_variant(struct FrameObject *base, FrameU8 group, FrameU8 variant)
{
 struct FrameTickObject *object=(struct FrameTickObject *)base;
 struct FramePartRecord *resource=(struct FramePartRecord *)&object->parts[0].variants[(signed char)group][(signed char)variant];
 object->variant=variant;
 object->variant_group=group;
 object->frame_delay=resource->frame_delay;
 frame_set_animation_resource(base,(struct FrameSpriteResource *)resource);
 if (resource->palette) {
  if (g_frame_flags & 0x10)
   display_load_palette_alternate(resource->palette, object->display.oam.palette * 16, 16);
  else
   display_queue_palette(resource->palette, object->display.oam.palette * 16, 16);
 }
}
