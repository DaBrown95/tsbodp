#include "frame_optional_choice_list.h"
unsigned char frame_optional_choice_classify(unsigned int index,unsigned int *value,unsigned char *first,unsigned char *last)
{
 register unsigned int table_offset asm("r0")=index+12;
 register const unsigned char **table asm("r5");
 register unsigned int base asm("r1");
 signed char hour;
 table_offset<<=24;
 base=(unsigned int)g_frame_scene_actor_world_tables;
 table_offset>>=22;
 table=(const unsigned char **)(table_offset+base);
 if(!*table)return 0;
 if((unsigned char)index==g_optional_choice_world.actor-18) {
  if((unsigned char)(g_optional_choice_world.clock.hour-9)<=7) {
   *value=50;
   return 1;
  }
  *last=display_time_weekday(&g_optional_choice_world.clock)+1;
  *first=9;
  *value=g_optional_choice_stage_values[g_optional_choice_world.stage];
 }else {
  *last=display_time_weekday(&g_optional_choice_world.clock);
  hour=g_optional_choice_world.clock.hour;
  *first=hour;
  *value=(*table+(signed char)hour*8)[*last];
  if(*value==50)return 1;
  do {
   hour++;
   if((signed char)hour>23) {
    (*last)++;
    *last=(unsigned int)*last%7;
    hour=0;
   }
  }while((*table+(signed char)hour*8)[*last]==*value);
  *first=hour;
 }
 return 1;
}
asm(".align 2, 0");
