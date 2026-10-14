#include "frame_palette_resource.h"
void frame_palette_resource_step(struct FrameObject *base) {
 struct FramePaletteResourceView *object=(struct FramePaletteResourceView *)base;
 if(object->state!=0) {
  if(object->state==1)object->flags|=2;
 }
}
