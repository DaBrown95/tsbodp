#include "frame_render_effect.h"
unsigned char frame_render_effect_terrain(struct FrameRenderEffect *effect){
 unsigned char terrain;
 struct FramePoint point;
 point.x=effect->position.pixel.x;
 point.y=effect->position.pixel.y;
 terrain=frame_map_terrain_at(point);
 effect->sprite.priority.layer=terrain/64+2;
 return terrain&0x3f;
}
