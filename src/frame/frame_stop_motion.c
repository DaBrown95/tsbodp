#include "frame_command.h"
void frame_stop_motion(struct FrameObject *object)
{
 object->acceleration.x = 0;
 object->acceleration.y = 0;
 object->velocity.x = 0;
 object->velocity.y = 0;
}
