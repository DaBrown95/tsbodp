#include "resource_conditions.h"
struct ConditionThresholdRecord { unsigned char unknown00[4],level; };
void condition_refresh_thresholds(void *record)
{
    struct ConditionThresholdRecord *state=record;
    if(state->level>4)condition_complete_if_active(1,4,2);
    if(state->level>29)condition_complete_if_active(4,0,2);
}
asm(".align 2, 0");
