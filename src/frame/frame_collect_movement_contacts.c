#include "frame_movement.h"
void frame_collect_movement_contacts(struct FrameObject *object)
{
    unsigned int flags=object->flags;
    ((struct FrameActorContactWork *)object)->contact=0;
    if(object->velocity.x || object->velocity.y) {
        if(flags&0x10040)frame_probe_movement_cells(object,g_frame_registration);
        if(flags&0x200)frame_refresh_movement_contacts(object);
    }
    if((flags&6)==4) {
        struct FrameObject **objects=(struct FrameObject **)g_frame_dispatch_scratch;
        unsigned int count=g_frame_dispatch_arg;
        objects[count]=object;
        g_frame_dispatch_arg=count+1;
    }
}
asm(".align 2, 0");
