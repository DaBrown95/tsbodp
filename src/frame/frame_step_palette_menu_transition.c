#include "frame_actor_palette_menu_transition.h"
void frame_step_palette_menu_transition(void)
{
 unsigned int timer=g_scene_request.unknown_14;
 if(timer==30) {
  struct FrameObject **objects;
  unsigned char i;
  display_set_window_rectangle(1,0,0,240*65536,160*65536);
  display_configure_window(1,63,60);
  display_set_background_scroll_target(1,0,-160*65536,15);
  display_set_background_scroll_target(0,0,-160*65536,15);
  display_begin_window_axis_move(1,0,0,160*65536,15);
  objects=g_frame_actor_palette_menu_objects;
  objects[8]->id=131;
  ((struct FrameActorObject *)objects[8])->need_timer=15;
  frame_set_variant_state(objects[8],57);
  objects[10]->id=132;
  ((struct FrameActorObject *)objects[10])->need_timer=15;
  frame_set_variant_state(objects[10],57);
  objects[14]->flags &= ~1u;
  objects[13]->flags &= ~1u;
  objects[12]->flags &= ~1u;
  objects[15]->id=135;
  ((struct FrameActorObject *)objects[15])->need_timer=15;
  frame_set_variant_state(objects[15],57);
  objects[16]->id=136;
  ((struct FrameActorObject *)objects[16])->need_timer=15;
  frame_set_variant_state(objects[16],57);
  for(i=0;i<g_frame_actor_palette_menu_exit_count;i++) {
   struct FrameObject *object=g_frame_actor_palette_menu_exit_objects[i];
   object->on_step=frame_scene_object_tick;
   transition_object_set_state(object,14);
   ((struct FrameActorObject *)object)->need_timer=16;
   frame_begin_position_move(object,object->position.x,199*65536,17);
   frame_step_position_move(object);
   frame_set_variant_state(object,3);
  }
 } else if(timer==15) {
  display_hide_background(0);
  display_hide_background(1);
  display_set_window_rectangle(1,0,0,240*65536,-176*65536);
  display_configure_window(1,60,56);
  display_set_background_scroll_target(2,0,176*65536,15);
  display_begin_window_axis_move(1,1,240*65536,-176*65536,7);
  g_frame_actor_palette_menu_objects[11]->id=133;
  ((struct FrameActorObject *)g_frame_actor_palette_menu_objects[11])->need_timer=7;
  frame_set_variant_state(g_frame_actor_palette_menu_objects[11],57);
 } else if(timer==1) {
  const char *text;
  display_hide_background(2);
  display_disable_window(1);
  g_frame_actor_palette_menu_text_flag=0;
  display_text_copy_field_zero((const char *)g_frame_actor_palette_menu_state.text);
  display_text_select_font(1,0,0);
  text=display_scene_lookup_text(0x184f);
  g_frame_actor_palette_menu_objects[7]=display_scene_create_label(9,&text);
  transition_object_set_state(g_frame_actor_palette_menu_objects[7],14);
 } else if(timer==0) {
  switch(g_scene_request.parameter) {
  case 13:display_scene_stage_08027dc0(5);break;
  case 6:
   g_scene_request.unknown_10=6;
   g_scene_request.unknown_14=31;
   frame_create_palette_menu_actors();
   goto enter_background;
  case 7:
   g_scene_request.unknown_10=6;
   g_scene_request.parameter=6;
   g_scene_request.unknown_14=31;
enter_background:
   /* This branch retains the captured zero through the background loads. */
   display_load_background(2,&g_frame_actor_palette_menu_background2,18,2,timer,timer);
   display_load_background(1,&g_frame_actor_palette_menu_background1,53,3,timer,timer);
   display_load_palette(g_frame_actor_palette_menu_entry_palette,64,16);
   {register unsigned int layer asm("r0")=2;register int horizontal asm("r1")=0*65536;int vertical=176*65536;display_set_background_scroll_target(layer,horizontal,vertical,1);}
   {register unsigned int layer asm("r0")=1;register int horizontal asm("r1")=256*65536;int vertical=0*65536;display_set_background_scroll_target(layer,horizontal,vertical,1);}
   {register unsigned int layer asm("r0")=0;register int horizontal asm("r1")=256*65536;int vertical=0*65536;display_set_background_scroll_target(layer,horizontal,vertical,1);}
   g_frame_actor_palette_menu_objects[0]->flags|=1;
   break;
  }
 }
 --g_scene_request.unknown_14;
}
asm(".align 2, 0");
