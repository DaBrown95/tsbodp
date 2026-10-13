#include "frame_map_scene.h"
void frame_define_palette_slot(unsigned int slot,const void *const *resources) {g_frame_map_palette_state.slots[slot].id=slot;g_frame_map_palette_state.slots[slot].sources=resources;resources+=g_frame_map_palette_state.frame;display_load_palette_alternate(*resources,slot<<4,16);}
asm(".align 2,0");
