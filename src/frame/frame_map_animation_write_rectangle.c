#include "frame_map_animation.h"

void frame_map_animation_write_rectangle(struct FrameObject *base) {
 struct FrameMapAnimationObject *object=(struct FrameMapAnimationObject *)base;
 struct FramePoint position;
 unsigned char current,row;
 unsigned int column;
 position.x=object->x.integer;position.y=object->y.integer;
 current=object->current;
 for(row=0;row<object->height;row++) {
  for(column=0;column<object->width;column=(unsigned char)(column+1)) {
   unsigned int map=object->map;
   unsigned short pixel_x=position.x,pixel_y=position.y;
   frame_write_map_cell(map,pixel_x,pixel_y,current);
   frame_write_extra_map_cell(pixel_x,pixel_y,current);
   position.x+=32;current++;
  }
  position.x=object->x.integer;position.y+=32;
 }
 object->current=current;
}
asm(".align 2, 0");
