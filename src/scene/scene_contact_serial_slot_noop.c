#include "scene_contact_serial_session_controller.h"

/* The installed on_step callback receives an object but consumes no input.
 * Additional historical unused formals remain unresolved. */
void scene_contact_serial_slot_noop(struct FrameObject *object)
{
    (void)object;
}
asm(".align 2, 0");
