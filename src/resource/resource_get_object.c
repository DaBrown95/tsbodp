#include "resource_groups.h"
#include "transition_object.h"

struct FrameObject *resource_get_object(unsigned int group, unsigned int slot)
{
    unsigned char *data;
    unsigned int group_id = (unsigned char)group;
    unsigned int slot_id = (unsigned char)slot;

    if (!group_id && slot_id > 0xFE) {
        unsigned char view = 0xFF - slot_id;
        struct TransitionViewContext *context = &g_transition_view_context;
        data = (unsigned char *)((unsigned int)view * sizeof(struct TransitionViewSlot)
                                + (unsigned int)context);
    } else {
        unsigned int offset;
        unsigned short *offsets;
        data = g_resource_object_data;
        offset = group_id << 1;
        offsets = (unsigned short *)(data + 2);
        data += *(unsigned short *)((unsigned char *)offsets + offset);
        offset = slot_id << 1;
        offsets = (unsigned short *)(data + 2);
        data += *(unsigned short *)((unsigned char *)offsets + offset);
    }
    return *(struct FrameObject **)data;
}
