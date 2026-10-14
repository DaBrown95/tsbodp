#include "resource_selection_stages.h"
unsigned int resource_selection_group_count_080456f4(void)
{
 switch(g_resource_selection_world.stage){
 case 0:case 1:return 0;
 case 2:case 3:return 3;
 case 4:return 2;
 default:return 0;
 }
}
