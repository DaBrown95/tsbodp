#include "resource_builders.h"
unsigned char *resource_build_program_group(const unsigned char *source,unsigned char *destination,unsigned char group) {
 unsigned int group_offset=group<<1;
 const unsigned short *offsets=(const unsigned short *)(source+2);
 const unsigned char *input=source+*(const unsigned short *)((const unsigned char *)offsets+group_offset);
 const struct ResourceProgramRecord *record;
 do {
  register unsigned short count asm("r1"); unsigned char index;
  record=(const struct ResourceProgramRecord *)input;
  count=g_resource_program_lengths[record->command];
  for(index=0;index<count;index++)*destination++=*input++;
 }while(record->command);
 return destination;
}
