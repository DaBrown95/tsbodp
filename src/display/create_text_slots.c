#include "frame.h"
#include "display_text_slots.h"

unsigned int display_create_text_slots(const char **text, unsigned int first_slot)
{
    unsigned char count = 0;

    do {
        struct FrameObject *object = display_allocate_text_object(text);
        g_display_text_slots[first_slot] = object;
        object->id = first_slot;
        count++;
        first_slot++;
    } while (**text);
    return count;
}

asm(".align 2,0");
