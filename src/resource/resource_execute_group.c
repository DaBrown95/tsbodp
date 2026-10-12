#include "resource_groups.h"

void resource_execute_group(unsigned char group) {
 unsigned char *data;
 unsigned int offset;
 unsigned short *offsets;
 unsigned char * position;
 struct ResourceProgramRecord *record;
 g_resource_current_program = group;
 data = g_resource_program_data;
 offset=group<<1;
 offsets=(unsigned short *)(data+2);
 position=data+*(unsigned short*)((unsigned char *)offsets+offset);
 do {
  unsigned char step;
  record = (struct ResourceProgramRecord *)position;
  if (!record->command) step=g_resource_program_lengths[0];
  else {
   g_resource_program_handlers[record->command](record);
   step=g_resource_program_lengths[record->command];
  }
  position+=step;
 } while (record->command);
}
