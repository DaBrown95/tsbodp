#include "frame_command.h"
FrameU8 frame_find_objects(FrameU8 id, FrameU8 subtype, struct FrameObject **results, FrameU8 capacity)
{
 FrameU8 count = 0;
 struct FrameObject *object;
 for (object = g_frame_primary_list.first; object && count < capacity; ) {
  struct FrameObject *next = object->next;
  if (object->id == id && object->unknown_0a == subtype)
  { results[count] = object;
    count++;
  }
  object = next;
 }
 return count;
}
asm(".align 2, 0");
