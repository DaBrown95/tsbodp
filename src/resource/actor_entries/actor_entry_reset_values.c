#include "resource_actor_entries.h"
void actor_entry_reset_values(struct ActorEntryContext *context) {
 unsigned int group;
 for(group=0;group<=12;++group)actor_entry_refresh_list(context,group);
 {unsigned int index=0;
 unsigned char *values=(unsigned char*)context+13;
 for(;index<=4;++index) {unsigned int spread=g_actor_entry_initial_values[index][1];values[index]=frame_random_bounded(spread*2)+g_actor_entry_initial_values[index][0]-spread;}
 }
}
asm(".align 2, 0");
