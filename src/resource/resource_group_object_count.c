#include "resource_builders.h"
unsigned short resource_group_object_count(unsigned char group)  {
    unsigned int offset;
    unsigned char *data=g_resource_object_data;
    unsigned short *offsets;
    offset=group<<1;
    offsets=(unsigned short *)(data+2);
    data+=*(unsigned short *)((unsigned char *)offsets+offset);
    return *(unsigned short *)data;
}
