#include "resource_groups.h"
#include "resource_object_payload.h"

unsigned char *resource_get_object_payload(unsigned int group, unsigned int slot)
{
    unsigned int group_index = (unsigned char)group;
    unsigned int slot_index = (unsigned char)slot;
    unsigned char *data = g_resource_object_data;

    group_index <<= 1;
    {
        unsigned short *offsets = (unsigned short *)(data + 2);
        data += *(unsigned short *)((unsigned char *)offsets + group_index);
    }
    slot_index <<= 1;
    {
        unsigned short *offsets = (unsigned short *)(data + 2);
        data += *(unsigned short *)((unsigned char *)offsets + slot_index);
    }
    return data + 8;
}

asm(".align 2,0");
