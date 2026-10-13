#include "frame_optional_choice_list.h"
void frame_optional_choice_begin(void)
{
 g_optional_choice_count=frame_optional_choice_build_available();
 if(frame_world_in_idle_exclusion_set(g_frame_world_id)) {
  g_need_effect_choice_text[0]=488;
  g_need_effect_choice_text[1]=489;
 }else g_need_effect_choice_text[0]=489;
 g_need_effect_choice_counters.value_4=0;
 g_need_effect_choice_counters.value_1=0;
 g_need_effect_choice_counters.value_2=0;
 display_scene_stage_08027dc0(2);
}
asm(".align 2, 0");
