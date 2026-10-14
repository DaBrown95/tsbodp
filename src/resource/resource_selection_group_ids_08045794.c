#include "resource_actor_selection.h"
void resource_selection_group_ids_08045794(int *groups) {
 switch(g_resource_selection_world.stage) {
case 0:case 1:break;
 case 2:groups[0]=23;groups[1]=25;groups[2]=24;break;
 case 3:groups[0]=46;groups[1]=48;groups[2]=47;break;
 case 4:groups[0]=39;groups[1]=40;groups[2]=-1;break;
 default:break;
 }

}
