#include "resource_conditions.h"
#include "condition_actor.h"
void condition_finish_actor_context(void *record)
{
 struct ConditionActorCounters *state=record;
 signed char *cell=(signed char *)&state->counters[0];
 int value=cell[3];
 if(value > 0)condition_complete_if_active(2,2,3);
 if(value > 4)condition_complete_if_active(3,3,1);
 cell=(signed char *)&state->counters[1];
 value=cell[3];
 if(value > 0)condition_complete_if_active(0,3,0);
 if(value > 1)condition_complete_if_active(2,0,1);
 cell=(signed char *)&state->counters[2];
 value=cell[3];
 if(value > 3)condition_complete_if_active(2,1,1);
 cell=(signed char *)&state->counters[5];
 if(value > 2 && cell[3]>1)condition_complete_if_active(3,2,2);
 cell=(signed char *)&state->counters[3];
 value=cell[3];
 if(value > 1)condition_complete_if_active(2,1,0);
 cell=(signed char *)&state->counters[4];
 value=cell[3];
 if(value > 3)condition_complete_if_active(3,0,2);
 if(value > 6)condition_complete_if_active(4,3,2);
}
