#include "display_menu_primary.h"
#include "frame_random.h"
extern const unsigned char g_display_menu_row_parameter_counts[];
unsigned int display_menu_primary_row_parameter(unsigned int row)
{
 unsigned int total=0;
 unsigned char *codes=(unsigned char *)&g_display_menu_state;
 unsigned char *code;
 unsigned int index;
 codes+=20;
 code=codes+row;
 if(*code<=21) if(*code!=22) {
  index=0;
  if(total<*code)do {
   total+=g_display_menu_row_parameter_counts[index];
   ++index;
  }while(index<*code);
  total+=frame_random_bounded((unsigned short)(g_display_menu_row_parameter_counts[index]-1));
 }
 return total;
}
asm(".align 2, 0");
