#include "frame_map_scene.h"
void frame_initialize_map_palette_slots(void) {unsigned char slot; for(slot=1;slot<=7;slot++)frame_define_palette_slot(slot,&g_frame_map_palette_resources[slot]);}
asm(".align 2,0");
