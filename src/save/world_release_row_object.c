#include "frame.h"
#include "save_world_initialization.h"

void save_world_release_row_object(struct SaveWorldTransitionRow *row,
                                   unsigned char index)
{
    unsigned int offset = index * 4;
    struct FrameObject **objects = row->objects;
    struct FrameObject **slot = (struct FrameObject **)
                                ((unsigned int)objects + offset);
    (*slot)->flags |= 2;
    *slot = 0;
}
asm(".align 2, 0");
