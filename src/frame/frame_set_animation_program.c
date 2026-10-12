#include "frame_tick.h"
void frame_set_animation_program(struct FrameObject *base, struct FrameSpriteResource *resource, FrameU8 *commands, FrameU8 skip)
{
 struct FrameTickObject *object = (struct FrameTickObject *)base;
 object->command_start = commands + skip * 2;
 object->commands = object->command_start;
 if (object->resource != resource) {
  object->resource = resource;
  object->previous_frame = 0xff;
  object->frame = -1;
 }
 frame_decode_animation_commands(base);
 frame_refresh_animation_bounds(base);
}
