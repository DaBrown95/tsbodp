#include "resource_groups.h"

void resource_spawn_group(unsigned char group) {
 unsigned char *data = g_resource_object_data;
 unsigned int group_offset=group<<1;
 unsigned short *group_offsets=(unsigned short *)(data+2);
 register unsigned int offset asm("r1")=*(unsigned short *)((unsigned char *)group_offsets+group_offset); unsigned char *entries=data+offset;
 unsigned char count = *entries, index;
 for (index=0; index<count; index++) {
  unsigned int entry_offset=index<<1;
  unsigned short *entry_offsets=(unsigned short *)(entries+2);
  register unsigned int offset asm("r1")=*(unsigned short *)((unsigned char *)entry_offsets+entry_offset); struct ResourceObjectEntry *entry=(struct ResourceObjectEntry *)(entries+offset);
  if (!entry->object) {
   unsigned int factory=entry->factory; register ResourceObjectFactory *table asm("r0")=g_resource_object_factories; entry->object = table[factory](group, index);
   if (entry->object) {
    entry->object->owner_id = group;
    entry->object->owner_slot = index;
    if (!entry->object->before_step)
     entry->object->before_step = resource_object_before_step;
    entry->object->flags |= 0x80000000;
   }
  }
 }
}
