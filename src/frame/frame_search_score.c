#include "frame_search.h"
void frame_search_score(struct FrameSearchRecord *record,unsigned int cost)
{
 signed char dx;
 unsigned char dy;
 unsigned int distance_x,distance_y;
 record->cost=cost;
 dx=g_frame_grid_search.target.axes.x-((unsigned char *)&record->cell)[0];
 dy=g_frame_grid_search.target.axes.y-((unsigned char *)&record->cell)[1];
 distance_x=dx;if(dx<0)distance_x=-dx;
 distance_y=(signed char)dy;if((signed char)dy<0)distance_y=-(signed char)dy;
 record->heuristic=distance_x+distance_y;
 record->priority=distance_x+distance_y+cost;
}
