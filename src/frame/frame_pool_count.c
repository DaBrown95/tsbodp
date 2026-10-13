#include "frame_search.h"
unsigned int frame_pool_count(void *head)
{
 unsigned int count=0;
 while((head=*(void **)head))count++;
 return count;
}
