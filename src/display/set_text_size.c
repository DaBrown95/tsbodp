#include "display_text.h"
#include "display_text_measure.h"
#include "display_scene_lifecycle.h"
void display_scene_set_text_size(struct FrameObject *base, const char *text)
{
 unsigned short width=display_text_measure_width(text),height=display_text_measure_height(text);
 int value;

 value=width; if(width>240) value=240; base->display_payload.text.width=value;
 value=height; if(height>16) value=16; base->display_payload.text.height=value;
 value=width+31;
 value=value/32;
 base->display_payload.text.columns=value;
 width=value<<2;
 height=(height+7)/8;
 width=(width*height)<<6;
 if(width!=base->display_bytes) {
  if(base->display_bytes) display_release_tile_bytes_immediately(base->display_index,base->display_bytes,base->double_tile_size);
  base->display_bytes=width;
  display_allocate_object_tiles(base,0);
 }
}
/* Keep the following function word aligned with zero padding. */
asm(".align 2, 0");
