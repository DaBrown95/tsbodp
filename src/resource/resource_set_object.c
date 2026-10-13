#include "resource_groups.h"

void resource_set_object(struct FrameObject *object, unsigned char group, unsigned char slot)
{
    unsigned char *data = g_resource_object_data;
    unsigned int group_offset = group << 1;
    unsigned int slot_offset;
    unsigned short *offsets = (unsigned short *)(data + 2);
    data += *(unsigned short *)((unsigned char *)offsets + group_offset);
    slot_offset = slot << 1;
    {
        unsigned short *slot_offsets = (unsigned short *)(data + 2);
        data += *(unsigned short *)((unsigned char *)slot_offsets + slot_offset);
    }
    *(struct FrameObject **)data = object;
}
