#include "frame_actor_attachment_parameters.h"

void frame_decrement_parameter_level_unrooted_3d1bc(void *record, unsigned int index)
{
    int previous = frame_read_signed_parameter(record, index);
    record = (unsigned char *)record + index * sizeof(unsigned int);
    *(unsigned int *)record = (unsigned int)(previous - 1) << 24;
}
asm(".align 2, 0");
