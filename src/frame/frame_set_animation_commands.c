#include "frame_tick.h"
void frame_set_animation_commands(struct FrameObject *base, FrameU8 *commands, FrameU8 skip)
{
 struct FrameTickObject *object = (struct FrameTickObject *)base;
 object->command_start = commands;
 object->commands = commands;
 if (commands) {
  object->command_start += skip * 2;
  object->commands += skip * 2;
  frame_decode_animation_commands(base);
  frame_refresh_animation_bounds(base);
 }
}
