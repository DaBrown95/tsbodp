#include "frame_scene_player.h"
struct FrameObject *frame_allocate_object(int id) {
 struct FrameObject *object=frame_allocate_scene_object();
 if(object){object->id=id;((unsigned char *)object)[0x84]=0;}
 return object;
}
asm(".align 2,0");
