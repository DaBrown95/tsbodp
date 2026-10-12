#include "scene.h"
#include "transition_object.h"
#include "background_animation.h"
#include "link_state.h"

void scene_initialize(void) {
 volatile unsigned short zero;
 int index;
 g_scene_id = g_scene_request.scene;
 if (g_link_flags & 0x8000) {
  scene_stage_0803e3a8();
  g_transition_view_context.count = 1;
  g_transition_view_context.current_view = 0;
  if (!(g_link_flags & 0x80000)) g_scene_mode_flags.flags |= 0x800000;
  g_link_flags &= ~0x8000;
  g_link_flags &= ~0x80000;
 }
 zero = 0;
 display_cpu_copy((const void *)&zero, (void *)0x06010000, 0x01004000);
 { unsigned short *end=g_scene_palette_indices,*p; unsigned short val=0; p=end+3; do { *p--=val; } while((int)p>=(int)end); }
 g_game_flags &= ~8;
 set_vblank_callback(scene_vblank_callback);
 display_set_mode(0);
 display_enable_layers(0x1000);
 display_configure_tile_allocation(0);
 display_show_background(0,g_scene_background_control0);
 display_show_background(1,g_scene_background_control1);
 display_show_background(2,g_scene_background_control2);
 if (g_scene_request.mode==4 || g_scene_request.mode==6 || g_scene_request.mode==5 || g_scene_request.mode==7) {
  if(g_scene_request.mode==4 || g_scene_request.mode==7) {
   int mode=(g_scene_request.mode==4 && g_scene_id==6) ? 6 : 0;
   { unsigned char *end=g_scene_mode_bytes,*p; p=end+3; do { *p--=mode; } while((int)p>=(int)end); }
  }
  scene_stage_08026b24();
  scene_stage_080301c4();
  g_scene_request.mode=0;
 }
 g_scene_context.resource=scene_lookup_resource(g_scene_world_state);
 display_load_palette(scene_palette_source(),0,256);
 g_palette_range_enabled_mask=0;
 scene_load_definition(g_scene_id);
 if(!g_scene_request.mode) {
  g_scene_world_state[0x736]=0;
  scene_stage_0802cd90();
  scene_stage_08026520(g_scene_id);
  scene_stage_08037444();
  if((g_scene_context.flags&1) && g_scene_id<=14) background_animation_load(1);
 } else if(g_scene_request.mode==2) {
  display_reset_tile_allocation();
  if(!(g_game_flags&0x40000)) scene_stage_0800125c();
  else scene_stage_080012dc();
  scene_stage_08001298(128);
  scene_stage_08000b78();
  scene_copy_palette_alternate(g_scene_context.palette,0,256);
  background_animation_load(g_background_animation.transfer_enabled);
  scene_stage_08009e18();
 }
 if(!(g_audio_control.flags&8))
  audio_select_sequence(scene_resource_audio_id(g_scene_context.resource));
 scene_initialize_objects(g_scene_entry_data,g_scene_id);
 scene_stage_08026bc8();
 if(g_scene_palette_range_configs[g_scene_id].resource)
  display_load_palette_ranges(g_scene_palette_range_configs[g_scene_id].resource);
 g_game_flags &= ~0x100000;
 if((g_game_flags&0x40020)!=0x40020) {
  for(index=0;index<g_transition_view_context.count;index++) {
   scene_initialize_view(index,0);
   scene_update_view(index);
  }
  for(index=0;index<g_transition_view_context.count;index++) {
   scene_show_view(index);
   scene_stage_0800e3a8(index);
  }
 } else {
  scene_initialize_view(g_transition_view_context.current_view,1);
  scene_update_view(g_transition_view_context.current_view);
 }
 if((g_game_flags&0x40020)==0x40020) transition_fade_black_in_record(0x3F);
 else transition_run_first(0x3F,0);
 background_animation_configure_alpha();
 g_game_flags &= ~0x40000;
 g_scene_request.mode=0;
}
