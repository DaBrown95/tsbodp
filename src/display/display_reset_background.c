#include "scene_display.h"
void display_reset_background(unsigned int index) {
 struct BackgroundState *state=&g_background_states[index];
 if(state->tilemap_source) display_release_memory(state->tilemap_source);
 scene_fill_bytes(state,0,108);
 state->flags=0x60;
 if(index>1) {
  state->scale=256;
  state->flags=0x68;
 }
}
