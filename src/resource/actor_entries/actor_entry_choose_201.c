#include "resource_actor_entries.h"
unsigned char actor_entry_choose_201(void){ unsigned char id;unsigned int mode;do{ id=frame_random_bounded(7)+201; mode=g_display_scene_catalog[id].unknown_10; }while(!mode || g_display_scene_catalog[id].id==317 || (mode==2 && frame_random_chance(50)) || (mode==3 && frame_random_chance(5)));return id;}
asm(".align 2, 0");
