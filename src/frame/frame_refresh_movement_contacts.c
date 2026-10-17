#include "frame_movement.h"
void frame_refresh_movement_contacts(struct FrameObject *object)
{
    int bounds[4];
    unsigned int contact;
    if(!(object->flags&0x1000000)) {
        g_frame_movement_filter[0]=255;
        contact=frame_get_movement_probe_bounds(object,bounds);
        {struct FramePoint position={(short)(object->next_position.word.x >> 16),(short)(object->next_position.word.y >> 16)};
        object->display_layer=frame_layer_at_position(position);}
        frame_apply_movement_contact(object,contact);
    }
}
asm(".align 2, 0");
