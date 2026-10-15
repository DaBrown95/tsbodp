#include "scene_resume.h"
#include "frame.h"
void frame_reset_primary_display_indices(void)
{
 struct FrameObject *object=g_frame_primary_list.first;
 while(object){
  object->display_index=0xffff;
  if(object->sharing_flags&0x40){
   unsigned char i;
   for(i=0;i<4;++i){
    object->parts[i].index|=0xffff;
    object->parts[i].bytes=0;
   }
  }
  object=object->next;
 }
}
