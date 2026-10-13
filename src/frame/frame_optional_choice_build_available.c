#include "frame_optional_choice_list.h"
unsigned char frame_optional_choice_build_available(void)
{
 unsigned int value;
 unsigned char first,second;
 unsigned char count=0,index=0;
 do {
  g_optional_choice_values[index].value|=255;
  index++;
 }while(index<=23);
 index=0;
 do {
  if(frame_optional_choice_classify(index,&value,&first,&second)) {
   if(display_menu_relation_initialized(&g_display_menu_relation_values,index)) {
    if(index!=13 || !condition_group_complete(4,4)) {
     g_optional_choice_values[count].value=index;
     count++;
    }
   }else if(index==5) {
    g_optional_choice_values[count].value=index;
    count++;
   }
  }
  index++;
 }while(index<=23);
 return count;
}
asm(".align 2, 0");
