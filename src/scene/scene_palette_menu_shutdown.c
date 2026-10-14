#include "scene_palette_menu.h"
void scene_palette_menu_shutdown(void){
 struct FrameActorPaletteMenuState *state=&g_frame_actor_palette_menu_state;unsigned int *choices=g_frame_actor_palette_menu_choices;
 state->selectors[0]=choices[0];state->selectors[1]=choices[1];state->selectors[2]=choices[2];state->selectors[3]=choices[3];state->selectors[4]=choices[4];state->selectors[5]=choices[5];state->selectors[6]=choices[6];
 transition_run_second(63,0);display_release_object_list(&g_frame_primary_list);display_reset();display_reset_palette_jobs();display_scene_clear_object_slots();heap_free(g_scene_palette_menu_owner);
}
asm(".align 2,0");
