#include "scene_contact_activity_three.h"
void scene_contact_activity_three_clear_slots(void) {
 unsigned int i;
 heap_clear(&g_scene_contact_activity_three_slots,0,104);
 for(i=0;i<=15;++i)g_scene_contact_activity_three_slots.objects[i]=0;
}
asm(".align 2,0");
