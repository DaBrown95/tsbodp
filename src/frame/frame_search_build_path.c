#include "frame_search.h"
unsigned char frame_search_build_path(struct FrameSearchNode *node)
{
 struct FrameSearchNode *following=0;
 if(node){
  struct FrameSearchNode *current=node;
  unsigned int count=0;
  while(((unsigned char *)&current->record.parent)[0] && ((unsigned char *)&current->record.parent)[1]){
   struct FrameSearchNode *previous;
   unsigned int use_following;
   g_frame_grid_search.cells[count]=current->record.cell;
   previous=frame_search_find_any(&current->record.parent);
   use_following=1;
   if(!previous)break;
   if(((unsigned char *)&previous->record.cell)[0]==((unsigned char *)&current->record.cell)[0]){
    following=frame_search_find_any(&previous->record.parent);
    count++;
    if(following && ((unsigned char *)&following->record.cell)[0]==((unsigned char *)&previous->record.cell)[0]){
     use_following=0;
     do{
      previous=following;
      following=frame_search_find_any(&previous->record.parent);
     }while(following && ((unsigned char *)&following->record.cell)[0]==((unsigned char *)&previous->record.cell)[0]);
    }
   }else{
    unsigned int previous_y=((unsigned char *)&previous->record.cell)[1];
    count++;
    if(previous_y==((unsigned char *)&current->record.cell)[1]){
     following=frame_search_find_any(&previous->record.parent);
     if(following && ((unsigned char *)&following->record.cell)[1]==((unsigned char *)&previous->record.cell)[1]){
      use_following=0;
      do{
       previous=following;
       following=frame_search_find_any(&previous->record.parent);
      }while(following && ((unsigned char *)&following->record.cell)[1]==((unsigned char *)&previous->record.cell)[1]);
     }
    }
   }
   current=previous;
   if(use_following==1&&following)current=following;
  }
  g_frame_grid_search.count=count;
  if(count)goto nonempty;
 }
 return 0;
 nonempty: return 1;
}
