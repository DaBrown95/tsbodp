#include "frame_optional_choice_list.h"
void frame_optional_choice_refresh(void)
{
 g_need_effect_choice_counters.value_4=0;
 frame_optional_choice_build_page();
 g_need_effect_choice_counters.value_1=0;
 g_need_effect_choice_counters.value_2=0;
 display_scene_stage_08027dc0(2);
}
