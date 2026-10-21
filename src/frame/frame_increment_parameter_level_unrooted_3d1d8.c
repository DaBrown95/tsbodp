#include "frame_actor_attachment_parameters.h"

void frame_increment_parameter_level_unrooted_3d1d8(void *record, unsigned int index)
{
    int previous = frame_read_signed_parameter(record, index);
    record = (unsigned char *)record + index * sizeof(unsigned int);
    *(unsigned int *)record = (unsigned int)(previous + 1) << 24;
}
asm(".align 2, 0");
