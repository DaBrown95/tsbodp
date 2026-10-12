#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
unsigned char frame_find_scene_target(int *x,int *y) { struct FrameObject *object,*next; for(object=g_frame_primary_list.first;object;object=next) { next=object->next; if(object->id==15) { *x=object->position.x;*y=object->position.y;return 1; } } return 0; }
asm(".align 2, 0");
