#include "scene_relation_grid.h"
void scene_relation_grid_sort_relations(const struct DisplayMenuRelationValues *values)
{
 unsigned int index,other,best;
 for(index=0;index<24;index++)g_scene_relation_grid_indices[index]=index;
 for(index=0;index<23;index++){
  best=index;
  for(other=index+1;other<24;other++)
   if(values->records[g_scene_relation_grid_indices[best]].value < values->records[g_scene_relation_grid_indices[other]].value)best=other;
  if(index!=best){unsigned int saved=g_scene_relation_grid_indices[index];g_scene_relation_grid_indices[index]=g_scene_relation_grid_indices[best];g_scene_relation_grid_indices[best]=saved;}
 }
}
asm(".align 2,0");
