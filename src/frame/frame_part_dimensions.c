#include "frame_animation.h"
void frame_part_dimensions(struct FrameObject *base, struct FramePoint *dimensions, FrameU8 part_index)
{
 struct FrameAnimationObject *object=(struct FrameAnimationObject *)base;
 int group=(signed char)object->variant_group;
 int variant=(signed char)object->variant;
 struct FrameSpriteSequence *sequence=object->parts[part_index].variants[group][variant].sequence;
 int wrap_previous=(FrameU8)object->parts[part_index].flags & 4;
 int frame;
 struct FrameAnimationFrame *record;
 if (wrap_previous || (object->parts[part_index].flags & 8)) {
  frame=object->animation.frame-1;
  if (frame<0) {
   if (wrap_previous) frame=sequence->frame_count-1;
   else frame=0;
  }
 } else frame=object->animation.frame;
 record=(struct FrameAnimationFrame *)((FrameU8 *)sequence+12+sequence->frame_offsets[frame]);
 dimensions->x=record->width;
 dimensions->y=record->height;
}
asm(".align 2, 0");
