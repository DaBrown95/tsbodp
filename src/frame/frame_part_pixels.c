#include "frame_animation.h"
struct FramePartRecord { const FrameU8 *data; struct FrameSpriteSequence *sequence; const FrameU8 *palette; FrameU8 frame_delay, unknown_0d[3]; };
const void *frame_part_pixels(struct FrameObject *base, FrameU8 part_index)
{
 struct FrameAnimationObject *object=(struct FrameAnimationObject *)base;
 FrameU8 group=object->variant_group;
 FrameU8 variant=object->variant;
 struct FramePartRecord *resource=(struct FramePartRecord *)&object->parts[part_index].variants[group][variant];
 struct FrameSpriteSequence *sequence=resource->sequence;
 int wrap_previous=(FrameU8)object->parts[part_index].flags & 4;
 int frame;
 unsigned int offset;
 if (wrap_previous || (object->parts[part_index].flags & 8)) {
  frame=object->animation.frame-1;
  if (frame<0) {
   if (wrap_previous) frame=sequence->frame_count-1;
   else frame=0;
  }
 } else frame=object->animation.frame;
 offset=sequence->frame_offsets[frame];
 offset += (unsigned int)sequence;
 return resource->data + *(FrameU16 *)(offset+16);
}
asm(".align 2, 0");
