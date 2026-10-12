#include "resource_commands.h"
#include "resource_conditions.h"
/* Partial four-byte meter records; values are interpreted as signed bytes here. */
struct ConditionMeter { unsigned char unknown00,value,unknown02[2]; };
struct ConditionThresholdState {
    unsigned char unknown00[0x22];
    short total;
    unsigned char count,unknown25[3];
    struct ConditionMeter meters[22];
};
static inline unsigned int cell_address(unsigned int row,unsigned int column,unsigned int entry) {
 unsigned int base=(unsigned int)&g_resource_game_state;
 unsigned int offset=entry*4;offset+=column*24;offset+=row*144;return offset+base;
}
#define available(row,column,entry) (!*(unsigned char*)(cell_address(row,column,entry)+0x449) && *(unsigned char*)(cell_address(row,column,entry)+0x448))
void condition_update_actor_context(void *context) {
 struct ConditionThresholdState *state=context;
 {
  unsigned char *count=&state->count;
  if(*count) {
   condition_complete_if_active(1,5,1);
   if(*count>3) {
    condition_complete_if_active(2,5,0);
    if(*count>7) {
     condition_complete_if_active(3,5,0);
     if(*count>12) condition_complete_if_active(4,5,0);
    }
   }
  }
 }
 if(state->total>24) {
  condition_complete_if_active(3,2,1);
  if(state->total>49) {
   condition_complete_if_active(4,0,3);
   if(state->total>59) condition_complete_if_active(4,2,1);
  }
 }
 if((signed char)state->meters[12].value>29) condition_complete_if_active(0,0,0);
 if((signed char)state->meters[0].value>24) condition_complete_if_active(1,3,0);
 if((signed char)state->meters[20].value>9) condition_complete_if_active(1,2,0);
 {
  signed char *field_a=(signed char*)&state->meters[6].value;
  int current_a=*field_a;
  signed char *value_a=field_a;
  if(current_a>39) condition_complete_if_active(2,0,0);
  if((signed char)state->meters[2].value>39) condition_complete_if_active(2,1,1);
  {
   signed char *field_b=(signed char*)&state->meters[5].value;
   int current_b=*field_b;
   signed char *value_b=field_b;
   if(current_b>29) condition_complete_if_active(2,3,1);
   if((signed char)state->meters[21].value>49) condition_complete_if_active(3,2,4);
   if((signed char)state->meters[9].value>59) condition_complete_if_active(3,3,0);
   {
    signed char *value=(signed char*)&state->meters[8].value;
    if(*value<=-50 && *value!=-128 && available(4,1,1)) condition_complete_if_active(4,1,1);
   }
   if(*value_a<=-50 && *value_a!=-128 && available(4,2,2)) resource_set_display_kind(97);
   if((signed char)state->meters[4].value>79 && available(4,3,1)) resource_set_display_kind(101);
   if(*value_b>59 && available(4,4,0)) resource_set_display_kind(104);
  }
 }
}
