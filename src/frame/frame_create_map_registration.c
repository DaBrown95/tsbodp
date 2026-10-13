#include "frame_map_scene.h"
void *frame_create_map_registration(unsigned short width,unsigned short height,unsigned char size) {struct FrameMapRegistration *registration=heap_allocate_zeroed(20);if(frame_initialize_map_registration(registration,width,height,size)==1) {unsigned int bytes=registration->extent*registration->extent;void *data=heap_allocate_zeroed(bytes);heap_clear(data,0,bytes);registration->data=data;}return registration;}
asm(".align 2,0");
