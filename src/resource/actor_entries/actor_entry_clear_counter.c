#include "resource_actor_entries.h"
unsigned char actor_entry_clear_counter(void *input,int index) {unsigned char *record=input; unsigned char *cell=record+4;unsigned char value=cell[index];cell[index]=0;return value;}
asm(".align 2, 0");
