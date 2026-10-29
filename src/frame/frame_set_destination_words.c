#include "frame.h"
void frame_set_destination_words(struct FrameObject *object,int x,int y)
{
 object->destination.x=x;
 object->destination.y=y;
}
