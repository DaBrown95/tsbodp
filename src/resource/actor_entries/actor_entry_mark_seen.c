#include "resource_actor_entries.h"
void actor_entry_mark_seen(unsigned int *words,unsigned int id) {if(id<=148)*(unsigned int*)((unsigned int)words+((id>>5)<<2))|=1<<(id&31);}
asm(".align 2, 0");
