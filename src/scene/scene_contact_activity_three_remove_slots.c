#include "scene_contact_activity_three.h"
void scene_contact_activity_three_remove_slots(void) {
 unsigned int i;
 for(i=0;i<=15;++i)if(g_scene_contact_activity_three_slots.objects[i]) {
  frame_remove_object(g_scene_contact_activity_three_slots.objects[i]);
  g_scene_contact_activity_three_slots.objects[i]=0;
 }
 g_scene_contact_activity_three_slots.count=0;
}
asm(".align 2,0");
