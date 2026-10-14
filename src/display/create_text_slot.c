#include "frame.h"
#include "display_text_slots.h"
struct FrameObject *display_create_text_slot(const char **text, unsigned int slot)
{
    struct FrameObject *object = display_allocate_text_object(text);
    g_display_text_slots[slot] = object;
    object->id = slot;
    return object;
}
asm(".align 2,0");
