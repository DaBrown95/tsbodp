#include "frame_render_effect.h"
#include "transition_object.h"
int frame_draw_render_effect(struct FrameRenderEffect *effect){
 unsigned int result=0;
 struct FrameSpriteSequence *sequence=effect->resource->sequence;
 struct FrameSpriteFrame *frame=(struct FrameSpriteFrame *)((unsigned char *)sequence+12+sequence->frame_offsets[effect->frame]);
 unsigned int count=frame->count_flags&0x1f;
 struct FrameSpritePart *part=(struct FrameSpritePart *)((unsigned char *)frame+10+sequence->collider_count*6+sequence->attachment_count*2);
 struct FramePoint origin;
 unsigned int tile_first;
 struct FrameOam initial,oam;
 unsigned char i;
 frame_get_view_origin(&origin,g_transition_view_context.current_view);
 if(effect->flags&0x200){
  origin.x=effect->position.pixel.x;
  origin.y=effect->position.pixel.y;
 }else{
  origin.x=effect->position.pixel.x-origin.x;
  origin.y=effect->position.pixel.y-origin.y;
 }
 if((unsigned int)origin.x>240 || origin.y<0 || origin.y>160)return 2;
 tile_first=effect->tile_first;
 tile_first+=effect->indices[effect->frame];
 initial=effect->sprite.attributes;
 for(i=0;i<count;i++){
  oam=initial;
  oam.tile=(unsigned short)(tile_first+part->tile);
  oam.size=part->size;
  oam.shape=part->shape;
  oam.x=origin.x+part->x;
  oam.y=origin.y+part->y;
  part++;
  result=(unsigned char)frame_append_oam(g_frame_display_channel,&oam);
 }
 return (signed char)result;
}
