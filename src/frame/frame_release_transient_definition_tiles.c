#include "frame_render_effect.h"
#include "frame_transient_effect.h"
void display_release_tile_bytes_immediately(FrameU16,FrameU32,FrameU8);
void frame_release_transient_definition_tiles(unsigned char group,unsigned char entry){
 unsigned short bytes=0;
 struct FrameSpriteSequence *sequence=((struct FrameSpriteResource *)g_frame_transient_definitions[group][entry].resource)->sequence;
 unsigned char frame;
 for(frame=0;frame<sequence->frame_count;frame++){
  struct FrameSpriteFrame *data=(struct FrameSpriteFrame *)((unsigned char *)sequence+12+sequence->frame_offsets[frame]);
  bytes+=data->width*data->height;
 }
 display_release_tile_bytes_immediately(g_frame_transient_definitions[group][entry].index,bytes,0);
}
