#include "frame_optional_choice_list.h"
void frame_optional_choice_open_secondary(void)
{
 g_need_effect_choice_counters.value_4=0;
 g_need_effect_choice_text[0]=492;
 g_need_effect_choice_text[1]=495;
 g_need_effect_choice_text[2]=493;
 if((unsigned char)condition_is_complete(4,0,0) && !(unsigned char)condition_is_complete(4,0,1))g_need_effect_choice_text[3]=497;
 g_need_effect_choice_counters.value_1=0;
 g_need_effect_choice_counters.value_2=0;
 display_scene_stage_08027dc0(2);
}
