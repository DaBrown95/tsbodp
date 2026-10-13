#include "frame_actor_attachment_parameters.h"
unsigned int frame_read_parameter_percentage(const void *record,unsigned int index){register unsigned int value asm("r0");unsigned int address=(unsigned int)record;address+=index*4;value=*(unsigned int *)address;value=(value<<8)>>8;value*=100;return value>>24;}
asm(".align 2, 0");
