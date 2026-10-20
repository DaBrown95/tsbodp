#include "scene_choice_panel.h"
void scene_choice_panel_shutdown(void)
{
 if(g_actor_scene_request.active==1 && g_actor_scene_request.object) g_actor_scene_request.object->flags|=2;
 heap_clear(&g_actor_scene_request,0,12);
 heap_clear(g_need_effect_choice_text,0,10);
 display_disable_window_layers();
 if(scene_queued_request_kind()==1)
  frame_disable_primary_object_flags(0x02000000U);
 else {
  transition_run_second(63,0);
  scene_retain_display();
  frame_clear_transient_effects();
  frame_clear_render_effects();
  frame_configure_deferred_display(0);
  display_reset_palette_jobs();
  display_reset();
  set_vblank_callback(irq_default_vblank_callback);
 }
}
asm(".align 2,0");
