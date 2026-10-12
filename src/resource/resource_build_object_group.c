#include "resource_builders.h"
unsigned char *resource_build_object_group(const unsigned char *source,unsigned char *destination,unsigned char group) {
 unsigned short stride;
 const unsigned char *source_group, *input;
 unsigned char *output;
 unsigned char count,index;
 unsigned int group_offset=group<<1;
 const unsigned short *offsets=(const unsigned short *)(source+2);
 stride=*(const unsigned short *)((const unsigned char *)offsets+group_offset);
 source_group=source+stride;
 input=source_group;
 output=destination;
 count=*source_group;
 *(unsigned short *)destination=count;
 stride=resource_align_word(count+2);
 input+=stride;
 stride=resource_offset_table_bytes(count+1);
 for(index=0;index<count;index++) {
  unsigned int entry_offset;
  destination+=stride;
  entry_offset=index<<1;
  { unsigned short *entry_offsets=(unsigned short *)(output+2); *(unsigned short *)((unsigned char *)entry_offsets+entry_offset)=destination-output; }
  { const unsigned char *sizes=source_group+2; stride=sizes[index]; }
  resource_copy_object_payload(input,destination,stride);
  input+=stride;
  stride+=8;
 }
 destination+=stride;
 return destination;
}
asm(".align 2, 0");
